#include "add_event_dialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

AddEventDialog::AddEventDialog(const QVector<Pet*>& petNames, QWidget *parent)
    : QDialog(parent),
      petComboBox(new QComboBox()),
      typeComboBox(new QComboBox()),
      descriptionEdit(new QLineEdit()),
      dateTimeEdit(new QDateTimeEdit(QDateTime::currentDateTime()))
{
    setWindowTitle("Добавить событие");

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* labelPet = new QLabel("Имя питомца:");
    petComboBox->addItems([this, &petNames]() {
        QStringList names;
        for (const Pet* pet : petNames) {
            names << pet->getName();
        }
        return names;
    }());

    layout->addWidget(labelPet);
    layout->addWidget(petComboBox);

    QLabel* labelType = new QLabel("Тип события:");
    typeComboBox->addItem("Кормление");
    typeComboBox->addItem("Прививка");
    typeComboBox->addItem("Груминг");
    typeComboBox->addItem("Прогулка");
    typeComboBox->addItem("Посещение ветеринара");
    typeComboBox->addItem("Тренировка");
    typeComboBox->addItem("Другое");

    layout->addWidget(labelType);
    layout->addWidget(typeComboBox);

    QLabel* labelTime = new QLabel("Дата и время:");
    dateTimeEdit->setCalendarPopup(true);
    layout->addWidget(labelTime);
    layout->addWidget(dateTimeEdit);

    QLabel* labelDesc = new QLabel("Описание:");
    layout->addWidget(labelDesc);
    layout->addWidget(descriptionEdit);

    QPushButton* okButton = new QPushButton("ОК");
    QPushButton* cancelButton = new QPushButton("Отмена");

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &AddEventDialog::onOkButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

AddEventDialog::~AddEventDialog()
{
    // Очистка не требуется — Qt удалит виджеты автоматически
}

Event AddEventDialog::getEvent() const
{
    QString petName = petComboBox->currentText();
    QString description = descriptionEdit->text();
    QDateTime dateTime = dateTimeEdit->dateTime();

    Event::Type type;
    switch (typeComboBox->currentIndex()) {
    case 0: type = Event::Type::Feeding; break;
    case 1: type = Event::Type::Vaccination; break;
    case 2: type = Event::Type::Grooming; break;
    case 3: type = Event::Type::Walk; break;
    case 4: type = Event::Type::VisitToVet; break;
    case 5: type = Event::Type::Training; break;
    default: type = Event::Type::Other; break;
    }

    return Event(petName, description, dateTime, type);
}

bool AddEventDialog::validate()
{
    if (petComboBox->currentText().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите питомца");
        return false;
    }

    if (descriptionEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите описание события");
        return false;
    }

    return true;
}

void AddEventDialog::onOkButtonClicked()
{
    if (!validate()) return;

    accept(); // Только если все данные корректны
}

void AddEventDialog::setPetIndex(int index)
{
    petComboBox->setCurrentIndex(index);
}

void AddEventDialog::setTypeIndex(int index)
{
    typeComboBox->setCurrentIndex(index);
}

void AddEventDialog::setDescription(const QString& text)
{
    descriptionEdit->setText(text);
}

void AddEventDialog::setDateTime(const QDateTime& dt)
{
    dateTimeEdit->setDateTime(dt);
}
