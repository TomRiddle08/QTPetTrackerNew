#include "mainwindow.h"
#include "add_event_dialog.h"
#include "edit_pet_dialog.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QStackedWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTimer>
#include <QColor>
#include <QBrush>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QDateTime>
#include <QLabel>
#include <QPixmap>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      stackedWidget(new QStackedWidget(this)),
      petTable(new QTableWidget()),
      eventTable(new QTableWidget())
{
    setCentralWidget(stackedWidget);

    // === Страница приветствия ===
    QWidget* welcomePage = new QWidget();
    welcomePage->setObjectName("welcomePage");
    QVBoxLayout* welcomeLayout = new QVBoxLayout(welcomePage);
    welcomeLayout->setAlignment(Qt::AlignCenter); // ✅ Горизонтальное центрирование
    welcomeLayout->setSpacing(20);

    QLabel* iconLabel = new QLabel();
    QPixmap iconPixmap(":/icons/pet_welcome.png");
    if (!iconPixmap.isNull()) {
        iconLabel->setPixmap(iconPixmap.scaled(150, 150, Qt::KeepAspectRatio));
    }
    iconLabel->setAlignment(Qt::AlignCenter);

    QLabel* titleLabel = new QLabel("Система управления питомцами");
    titleLabel->setFont(QFont("Segoe UI", 16, QFont::Bold));
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel* subtitleLabel = new QLabel("Версия 1.0 | Автор: Фёдоров Михаил"); //
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setFont(QFont("Segoe UI", 10));

    QPushButton* startButton = new QPushButton("Начать");
    startButton->setFixedWidth(200);
    startButton->setFixedHeight(40);
    startButton->setFont(QFont("Segoe UI", 12, QFont::Bold));

    connect(startButton, &QPushButton::clicked, this, &MainWindow::showMainPage);

    // ✅ Добавляем растягивающие элементы для горизонтального центрирования
    welcomeLayout->addStretch(); // Выравнивание до кнопки
    welcomeLayout->addWidget(iconLabel);
    welcomeLayout->addWidget(titleLabel);
    welcomeLayout->addWidget(subtitleLabel);
    welcomeLayout->addWidget(startButton);
    welcomeLayout->addStretch(); // Выравнивание после кнопки

    stackedWidget->addWidget(welcomePage); // Индекс 0 — Приветствие
    stackedWidget->setCurrentIndex(0);     // Открываем стартовый экран

    // === Страница "Питомцы" ===
    QWidget* petsPage = new QWidget();
    QVBoxLayout* petsLayout = new QVBoxLayout();

    petTable->setColumnCount(7);
    petTable->setHorizontalHeaderLabels({"Имя", "ФИО владельца", "Порода", "Возраст", "Вес", "Окрас", "Описание"});
    petTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    petTable->verticalHeader()->setVisible(false);

    QPushButton* addPetButton = new QPushButton("Добавить питомца");
    QPushButton* editPetButton = new QPushButton("Редактировать");
    QPushButton* goToEventsButton = new QPushButton("Перейти к событиям");
    QPushButton* checkNowButton = new QPushButton("Проверить напоминания");

    QHBoxLayout* petsButtonsLayout = new QHBoxLayout();
    petsButtonsLayout->addWidget(addPetButton);
    petsButtonsLayout->addWidget(editPetButton);
    petsButtonsLayout->addWidget(goToEventsButton);
    petsButtonsLayout->addWidget(checkNowButton);

    connect(addPetButton, &QPushButton::clicked, this, &MainWindow::addPetButtonClicked);
    connect(editPetButton, &QPushButton::clicked, this, &MainWindow::editPetButtonClicked);
    connect(goToEventsButton, &QPushButton::clicked, this, &MainWindow::showEventsPage);
    connect(checkNowButton, &QPushButton::clicked, this, &MainWindow::checkNowButtonClicked);

    petsLayout->addWidget(petTable);
    petsLayout->addLayout(petsButtonsLayout); // Добавляем layout с кнопками

    petsPage->setLayout(petsLayout);

    // === Страница "События" ===
    QWidget* eventsPage = new QWidget();
    QVBoxLayout* eventsLayout = new QVBoxLayout();

    eventTable->setColumnCount(5);
    eventTable->setHorizontalHeaderLabels({"Выбор", "Имя питомца", "Тип события", "Дата и время", "Описание"});
    eventTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    eventTable->verticalHeader()->setVisible(false);
    QPushButton* addEventButton = new QPushButton("Добавить событие");
    QPushButton* editEventButton = new QPushButton("Изменить");
    QPushButton* removeEventButton = new QPushButton("Удалить");
    QPushButton* backToPetsButton = new QPushButton("Назад к питомцам");

    QHBoxLayout* eventsButtonsLayout = new QHBoxLayout();
    eventsButtonsLayout->addWidget(addEventButton);
    eventsButtonsLayout->addWidget(editEventButton);
    eventsButtonsLayout->addWidget(removeEventButton);

    connect(addEventButton, &QPushButton::clicked, this, &MainWindow::addEventButtonClicked);
    connect(editEventButton, &QPushButton::clicked, this, &MainWindow::editEventButtonClicked);
    connect(removeEventButton, &QPushButton::clicked, this, &MainWindow::removeEventButtonClicked);
    connect(backToPetsButton, &QPushButton::clicked, this, &MainWindow::showPetsPage);

    eventsLayout->addWidget(eventTable);
    eventsLayout->addLayout(eventsButtonsLayout);
    eventsLayout->addWidget(backToPetsButton);

    eventsPage->setLayout(eventsLayout);

    // Добавляем страницы в стек
    stackedWidget->addWidget(petsPage);   // Индекс 1 — Питомцы
    stackedWidget->addWidget(eventsPage); // Индекс 2 — События

    // === После загрузки данных ===
    loadData(); // Загружаем из файла
    updatePetTable();
    updateEventTable();

    // === Здесь вставляем вызов стиля (если используешь style.qss) ===
    loadApplicationStyle(":/new/prefix1/styles.qss");


    // === Здесь настраиваем системный трей и напоминания ===
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        setupTrayIcon();
    }
    setupReminders();
}

MainWindow::~MainWindow()
{
    saveData(); // Сохраняем перед выходом
    qDeleteAll(pets);

    if (trayIcon) {
        trayIcon->hide();
        delete trayIcon;
    }
}
void MainWindow::showMainPage()
{
    stackedWidget->setCurrentIndex(1); // Переключаемся на главный экран
}
void MainWindow::setupTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/new/prefix1/img/pets.png")); // Путь к иконке, добавленной в ресурсы
    trayIcon->setToolTip("Система управления питомцами");

    // Контекстное меню (по желанию)
    QMenu* trayMenu = new QMenu(this);
    QAction* quitAction = trayMenu->addAction("Выход");
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}
void MainWindow::checkNowButtonClicked()
{
    qDebug() << "[DEBUG] Ручная проверка напоминаний...";
    checkReminders();
}

void MainWindow::setupReminders()
{
    reminderTimer = new QTimer(this);
    connect(reminderTimer, &QTimer::timeout, this, &MainWindow::checkReminders);
    reminderTimer->start(60000); // Проверяем каждую минуту
}
void MainWindow::checkReminders()
{
    QDateTime now = QDateTime::currentDateTime();

    for (const Event& event : events) {
        qint64 secondsLeft = event.getDateTime().toSecsSinceEpoch() - now.toSecsSinceEpoch();

        if (secondsLeft > 0 && secondsLeft <= 3600) { // За час до события
            QString message = QString("Напоминание:\nПитомец: %1\nСобытие: %2\nВремя: %3")
                .arg(event.getPetName())
                .arg(event.getDescription())
                .arg(event.getDateTime().toString("dd.MM.yyyy hh:mm"));

            if (trayIcon && trayIcon->isVisible()) {
                trayIcon->showMessage("Напоминание", message, QSystemTrayIcon::Information, 5000);
            } else {
                QMessageBox::information(nullptr, "Напоминание", message);
            }
        }
    }
}

void MainWindow::showPetsPage()
{
    stackedWidget->setCurrentIndex(1);
    updatePetTable();
}

void MainWindow::showEventsPage()
{
    stackedWidget->setCurrentIndex(2);
    updateEventTable();
}
void MainWindow::addPetButtonClicked()
{
    EditPetDialog dialog(pets, this);
    dialog.setAddMode(true);
    if (dialog.exec() == QDialog::Accepted) {
        Pet* pet = new Pet(
            dialog.getName(),
            dialog.getOwner(),
            dialog.getBreed(),
            dialog.getAge(),
            dialog.getWeight(),
            dialog.getColor(),
            dialog.getDescription()
        );
        pets.append(pet);
        updatePetTable();
    }
}
void MainWindow::editPetButtonClicked()
{
    bool ok;
    QString name = QInputDialog::getItem(this, "Выберите питомца", "Питомец:",
        [this]() {
            QStringList names;
            for (Pet* pet : pets)
                names << pet->getName();
            return names;
        }(), 0, false, &ok);

    if (!ok || name.isEmpty()) return;

    for (Pet* pet : pets) {
        if (pet->getName() == name) {
            EditPetDialog dialog(pets, this);
            dialog.setPet(pet);
            dialog.setAddMode(false);
            if (dialog.exec() == QDialog::Accepted) {
                pet->setName(dialog.getName());
                pet->setOwner(dialog.getOwner());
                pet->setBreed(dialog.getBreed());
                pet->setAge(dialog.getAge());
                pet->setWeight(dialog.getWeight());
                pet->setColor(dialog.getColor());
                pet->setDescription(dialog.getDescription());
                updatePetTable();
            }
            break;
        }
    }
}
void MainWindow::addEventButtonClicked()
{
    AddEventDialog dialog(pets, this);
    if (dialog.exec() == QDialog::Accepted) {
        Event event = dialog.getEvent();
        events.append(event);
        updateEventTable();
    }
}
void MainWindow::editEventButtonClicked()
{
    for (int row = 0; row < eventTable->rowCount(); ++row) {
        QTableWidgetItem* cbItem = eventTable->item(row, 0);
        if (cbItem && cbItem->checkState() == Qt::Checked && row < events.size()) {
            Event oldEvent = events[row];

            AddEventDialog dialog(pets, this);
            for (int i = 0; i < pets.size(); ++i) {
                if (pets[i]->getName() == oldEvent.getPetName()) {
                    dialog.setPetIndex(i);
                    break;
                }
            }

            dialog.setDescription(oldEvent.getDescription());
            dialog.setDateTime(oldEvent.getDateTime());

            switch (oldEvent.getType()) {
            case Event::Type::Feeding: dialog.setTypeIndex(0); break;
            case Event::Type::Vaccination: dialog.setTypeIndex(1); break;
            default: dialog.setTypeIndex(2); break;
            }

            if (dialog.exec() == QDialog::Accepted) {
                events[row] = dialog.getEvent();
                updateEventTable();
            }

            break;
        }
    }
}
void MainWindow::removeEventButtonClicked()
{
    QList<int> selectedRows;

    for (int row = 0; row < eventTable->rowCount(); ++row) {
        QTableWidgetItem* cbItem = eventTable->item(row, 0);
        if (cbItem && cbItem->checkState() == Qt::Checked) {
            selectedRows.append(row);
        }
    }

    std::sort(selectedRows.begin(), selectedRows.end(), std::greater<int>());
    foreach (int row, selectedRows) {
        if (row >= 0 && row < events.size()) {
            events.removeAt(row);
        }
    }

    updateEventTable();
}
void MainWindow::updatePetTable()
{
    petTable->setRowCount(0);

    for (Pet* pet : pets) {
        int row = petTable->rowCount();
        petTable->insertRow(row);

        petTable->setItem(row, 0, new QTableWidgetItem(pet->getName()));
        petTable->setItem(row, 1, new QTableWidgetItem(pet->getOwner()));
        petTable->setItem(row, 2, new QTableWidgetItem(pet->getBreed()));
        petTable->setItem(row, 3, new QTableWidgetItem(QString::number(pet->getAge())));
        petTable->setItem(row, 4, new QTableWidgetItem(QString::number(pet->getWeight(), 'f', 1)));
        petTable->setItem(row, 5, new QTableWidgetItem(pet->getColor()));
        petTable->setItem(row, 6, new QTableWidgetItem(pet->getDescription()));

        // Убедись, что UserRole установлен для цветов событий, если используешь QSS стили
        QTableWidgetItem* typeItem = petTable->item(row, 2); // порода
        if (typeItem)
            typeItem->setData(Qt::UserRole, "pet_row");
    }
}
void MainWindow::updateEventTable()
{
    eventTable->setRowCount(0);

    if (events.isEmpty()) {
        int row = eventTable->rowCount(); // ✅ Объявляем row до использования
        eventTable->insertRow(row);

        auto* checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkBoxItem->setCheckState(Qt::Unchecked);
        eventTable->setItem(row, 0, checkBoxItem);

        eventTable->setItem(row, 1, new QTableWidgetItem("—"));
        eventTable->setItem(row, 2, new QTableWidgetItem("—"));
        eventTable->setItem(row, 3, new QTableWidgetItem("—"));
        eventTable->setItem(row, 4, new QTableWidgetItem("Нет событий"));

        return;
    }

    for (const Event& event : events) {
        int row = eventTable->rowCount(); // ✅ Теперь row объявлен правильно
        eventTable->insertRow(row);

        // Чекбокс
        auto* checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkBoxItem->setCheckState(Qt::Unchecked);
        eventTable->setItem(row, 0, checkBoxItem);

        eventTable->setItem(row, 1, new QTableWidgetItem(event.getPetName()));
        eventTable->setItem(row, 2, new QTableWidgetItem(event.getTypeString()));
        eventTable->setItem(row, 3, new QTableWidgetItem(event.getDateTime().toString("dd.MM.yyyy hh:mm")));
        eventTable->setItem(row, 4, new QTableWidgetItem(event.getDescription()));

        // Устанавливаем UserRole для типа события
        QTableWidgetItem* typeItem = eventTable->item(row, 2);
        if (typeItem) {
            switch (event.getType()) {
            case Event::Type::Feeding:
                typeItem->setData(Qt::UserRole, "feeding");
                break;
            case Event::Type::Vaccination:
                typeItem->setData(Qt::UserRole, "vaccination");
                break;
            case Event::Type::Grooming:
                typeItem->setData(Qt::UserRole, "grooming");
                break;
            case Event::Type::Walk:
                typeItem->setData(Qt::UserRole, "walk");
                break;
            case Event::Type::VisitToVet:
                typeItem->setData(Qt::UserRole, "visit_to_vet");
                break;
            case Event::Type::Training:
                typeItem->setData(Qt::UserRole, "training");
                break;
            default:
                typeItem->setData(Qt::UserRole, "other");
                break;
            }
        }
    }
}
QString MainWindow::dataFilePath() const
{
    return QApplication::applicationDirPath() + "/data.json";
}
void MainWindow::saveData()
{
    QJsonObject root;
    QJsonArray petsArray;

    for (Pet* pet : pets) {
        QJsonObject petObj;
        petObj["name"] = pet->getName();
        petObj["owner"] = pet->getOwner();
        petObj["breed"] = pet->getBreed();
        petObj["age"] = pet->getAge();
        petObj["weight"] = pet->getWeight();
        petObj["color"] = pet->getColor();
        petObj["description"] = pet->getDescription();
        petsArray.append(petObj);
    }

    QJsonArray eventsArray;
    for (const Event& event : events) {
        QJsonObject eventObj;
        eventObj["petName"] = event.getPetName();
        eventObj["description"] = event.getDescription();
        eventObj["dateTime"] = event.getDateTime().toString(Qt::ISODate);
        eventObj["type"] = static_cast<int>(event.getType());
        eventsArray.append(eventObj);
    }

    root["pets"] = petsArray;
    root["events"] = eventsArray;

    QJsonDocument doc(root);
    QFile file(dataFilePath());
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Ошибка", "Не могу сохранить данные.");
        return;
    }

    file.write(doc.toJson());
    file.close();
}
void MainWindow::loadData()
{
    QFile file(dataFilePath());
    if (!file.exists()) return;

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Ошибка", "Не могу загрузить данные.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();

    // Загружаем питомцев
    QJsonArray petsArray = root["pets"].toArray();
    foreach (const QJsonValue& value, petsArray) {
        QJsonObject obj = value.toObject();
        Pet* pet = new Pet(
            obj["name"].toString(),
            obj["owner"].toString(),
            obj["breed"].toString(),
            obj["age"].toInt(),
            obj["weight"].toDouble(),
            obj["color"].toString(),
            obj["description"].toString()
        );
        pets.append(pet);
    }

    // Загружаем события
    QJsonArray eventsArray = root["events"].toArray();
    foreach (const QJsonValue& value, eventsArray) {
        QJsonObject obj = value.toObject();
        Event::Type type = static_cast<Event::Type>(obj["type"].toInt());

        Event event(
            obj["petName"].toString(),
            obj["description"].toString(),
            QDateTime::fromString(obj["dateTime"].toString(), Qt::ISODate),
            type
        );

        events.append(event);
    }

    updatePetTable();
    updateEventTable();
}
void MainWindow::loadApplicationStyle(const QString& path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "Не могу открыть стиль по пути:" << path;
        return;
    }

    QString styleSheet = QTextStream(&file).readAll();
    qApp->setStyleSheet(styleSheet);
    file.close();
}

