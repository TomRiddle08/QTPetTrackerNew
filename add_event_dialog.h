#ifndef ADD_EVENT_DIALOG_H
#define ADD_EVENT_DIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QVector>
#include "event.h"
#include "pet.h"

class AddEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEventDialog(const QVector<Pet*>& petNames, QWidget *parent = nullptr);
    ~AddEventDialog();

    Event getEvent() const;

    void setPetIndex(int index);
    void setTypeIndex(int index);
    void setDescription(const QString& text);
    void setDateTime(const QDateTime& dt);

private slots:
    void onOkButtonClicked(); // ✅ Теперь объявлен

private:
    QComboBox* petComboBox;
    QComboBox* typeComboBox;
    QLineEdit* descriptionEdit;
    QDateTimeEdit* dateTimeEdit;

    bool validate(); // ✅ Объявляем validate()
};

#endif // ADD_EVENT_DIALOG_H
