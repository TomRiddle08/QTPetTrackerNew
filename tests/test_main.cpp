#include <QtTest>
#include "../mainwindow.h"
#include "../event.h"
#include "../pet.h"

class TestAll : public QObject {
    Q_OBJECT
private slots:
    void testExample() {
        QVERIFY(1 + 1 == 2);
    }
};

QTEST_APPLESS_MAIN(TestAll)
#include "test_main.moc"