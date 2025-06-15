#include <QtTest>
#include "../event.h"
#include "../pet.h"

class TestBasic : public QObject
{
    Q_OBJECT
private slots:
    void testEventCreation() {
        Event e("2025-06-15", "Vaccine", "Rabies");
        QCOMPARE(e.getType(), QString("Vaccine"));
    }
    
    void testPetCreation() {
        Pet p("Fluffy", "Cat", 2);
        QCOMPARE(p.getSpecies(), QString("Cat"));
    }
};

QTEST_APPLESS_MAIN(TestBasic)
#include "test_main.moc"