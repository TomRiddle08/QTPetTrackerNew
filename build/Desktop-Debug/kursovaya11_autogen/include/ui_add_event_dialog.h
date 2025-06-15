/********************************************************************************
** Form generated from reading UI file 'add_event_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_EVENT_DIALOG_H
#define UI_ADD_EVENT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_add_event_dialog
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *petComboBox;
    QComboBox *typeComboBox;
    QDateTimeEdit *dateTimeEdit;
    QLineEdit *desriptionEdit;

    void setupUi(QDialog *add_event_dialog)
    {
        if (add_event_dialog->objectName().isEmpty())
            add_event_dialog->setObjectName("add_event_dialog");
        add_event_dialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(add_event_dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        petComboBox = new QComboBox(add_event_dialog);
        petComboBox->setObjectName("petComboBox");
        petComboBox->setGeometry(QRect(40, 70, 79, 26));
        typeComboBox = new QComboBox(add_event_dialog);
        typeComboBox->setObjectName("typeComboBox");
        typeComboBox->setGeometry(QRect(130, 70, 79, 26));
        dateTimeEdit = new QDateTimeEdit(add_event_dialog);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(40, 110, 194, 27));
        desriptionEdit = new QLineEdit(add_event_dialog);
        desriptionEdit->setObjectName("desriptionEdit");
        desriptionEdit->setGeometry(QRect(40, 150, 113, 26));

        retranslateUi(add_event_dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, add_event_dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, add_event_dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(add_event_dialog);
    } // setupUi

    void retranslateUi(QDialog *add_event_dialog)
    {
        add_event_dialog->setWindowTitle(QCoreApplication::translate("add_event_dialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class add_event_dialog: public Ui_add_event_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_EVENT_DIALOG_H
