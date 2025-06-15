#ifndef EDIT_PET_DIALOG_H
#define EDIT_PET_DIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QVector>
#include "pet.h"

class EditPetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPetDialog(const QVector<Pet*>& allPets, QWidget *parent = nullptr);
    ~EditPetDialog();

    QString getName() const;
    QString getOwner() const;
    QString getBreed() const;
    int getAge() const;
    double getWeight() const;
    QString getColor() const;
    QString getDescription() const;

    void setPet(const Pet* pet);

    bool validate(); // Проверка обязательных полей

    void setAddMode(bool isAdding);

private slots:
    void onOkButtonClicked(); // Слот для "ОК"

private:
    QComboBox* petComboBox;
    QLineEdit* nameEdit;
    QLineEdit* ownerEdit;
    QLineEdit* breedEdit;
    QSpinBox* ageEditBox;
    QDoubleSpinBox* weightEditBox;
    QLineEdit* colorEdit;
    QLineEdit* descriptionEdit;
};

#endif // EDIT_PET_DIALOG_H
