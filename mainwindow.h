#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QList>
#include "pet.h"
#include "event.h"

QT_BEGIN_NAMESPACE
class QStackedWidget;
class QTableWidget;
class QPushButton;
class QTimer;
class QSystemTrayIcon;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showPetsPage();
    void showEventsPage();
    void addPetButtonClicked();
    void editPetButtonClicked();
    void addEventButtonClicked();
    void editEventButtonClicked();
    void removeEventButtonClicked();
    void checkNowButtonClicked(); // ← Новый метод

private:
    void loadApplicationStyle(const QString& path); // Загрузка QSS
    void updatePetTable();
    void updateEventTable();
    void saveData();
    void loadData();
    void showWelcomePage();
    void showMainPage();
    QString dataFilePath() const;

    void setupTrayIcon();  // Настройка системного трея
    void setupReminders(); // Запуск таймера
    void checkReminders();

    QStackedWidget* stackedWidget;
    QTableWidget* petTable;
    QTableWidget* eventTable;

    QPushButton* addPetButton;
    QPushButton* editPetButton;
    QPushButton* goToEventsButton;
    QPushButton* backToPetsButton;
    QPushButton* addEventButton;
    QPushButton* editEventButton;
    QPushButton* removeEventButton;
    QPushButton * startButtob;

    QVector<Pet*> pets;
    QList<Event> events;

    QTimer* reminderTimer;
    QSystemTrayIcon* trayIcon;
};

#endif // MAINWINDOW_H
