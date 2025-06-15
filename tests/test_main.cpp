#include <QtTest>
#include "../event.h"
#include "../pet.h"

class TestBasic : public QObject
{
    Q_OBJECT
private slots:
    void testEventCreation()
    {
        QDateTime dt = QDateTime::currentDateTime();
        Event e("Барсик", "Ежегодная прививка", dt, Event::Type::Vaccination);
        
        QCOMPARE(e.getPetName(), QString("Барсик"));
        QCOMPARE(e.getType(), Event::Type::Vaccination); // Сравниваем enum
        QCOMPARE(e.getTypeString(), QString("Прививка")); // Сравниваем строки
    }
    
    void testPetCreation()
    {
        Pet p("Мурзик", "Кот", "Домашний", 3, 4.5, "Рыжий", "Пушистый");
        
        QCOMPARE(p.getName(), QString("Мурзик"));
        QCOMPARE(p.getBreed(), QString("Домашний")); // Используем существующий метод
    }
};

QTEST_APPLESS_MAIN(TestBasic)
#include "test_main.moc"