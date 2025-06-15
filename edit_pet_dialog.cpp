#include "edit_pet_dialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QMessageBox>

EditPetDialog::EditPetDialog(const QVector<Pet*>& allPets, QWidget *parent)
    : QDialog(parent),
      petComboBox(new QComboBox()),
      nameEdit(new QLineEdit()),
      ownerEdit(new QLineEdit()),
      breedEdit(new QLineEdit()),
      ageEditBox(new QSpinBox()),
      weightEditBox(new QDoubleSpinBox()),
      colorEdit(new QLineEdit()),
      descriptionEdit(new QLineEdit())
{
    setWindowTitle("Добавить / Редактировать питомца");

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* labelPet = new QLabel("Выберите питомца:");
    petComboBox->addItems([this, &allPets]() {
        QStringList names;
        for (const Pet* pet : allPets) {
            names << pet->getName();
        }
        return names;
    }());

    layout->addWidget(labelPet);
    layout->addWidget(petComboBox);

    layout->addWidget(new QLabel("Имя:"));         layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("ФИО владельца:")); layout->addWidget(ownerEdit);
    layout->addWidget(new QLabel("Порода:"));      layout->addWidget(breedEdit);
    layout->addWidget(new QLabel("Возраст:"));       layout->addWidget(ageEditBox);
    layout->addWidget(new QLabel("Вес:"));          layout->addWidget(weightEditBox);
    layout->addWidget(new QLabel("Окрас:"));        layout->addWidget(colorEdit);
    layout->addWidget(new QLabel("Описание:"));     layout->addWidget(descriptionEdit);

    QPushButton* okButton = new QPushButton("ОК");
    QPushButton* cancelButton = new QPushButton("Отмена");

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &EditPetDialog::onOkButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

EditPetDialog::~EditPetDialog()
{
    // Очистка не требуется — Qt удалит виджеты автоматически
}

QString EditPetDialog::getName() const {
    return nameEdit->text();
}

QString EditPetDialog::getOwner() const {
    return ownerEdit->text();
}

QString EditPetDialog::getBreed() const {
    return breedEdit->text();
}

int EditPetDialog::getAge() const {
    return ageEditBox->value();
}

double EditPetDialog::getWeight() const {
    return weightEditBox->value();
}

QString EditPetDialog::getColor() const {
    return colorEdit->text();
}

QString EditPetDialog::getDescription() const {
    return descriptionEdit->text();
}

void EditPetDialog::setPet(const Pet* pet)
{
    nameEdit->setText(pet->getName());
    ownerEdit->setText(pet->getOwner());
    breedEdit->setText(pet->getBreed());
    ageEditBox->setValue(pet->getAge());
    weightEditBox->setValue(pet->getWeight());
    colorEdit->setText(pet->getColor());
    descriptionEdit->setText(pet->getDescription());
}

bool EditPetDialog::validate()
{
    if (nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Кличка питомца обязательна");
        return false;
    }

    if (ownerEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "ФИО владельца обязательно");
        return false;
    }

    if (breedEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Порода питомца обязательна");
        return false;
    }

    return true;
}

void EditPetDialog::onOkButtonClicked()
{
    if (!validate()) return;

    accept(); // Закрываем диалог, только если всё верно
}
void EditPetDialog::setAddMode(bool isAdding)
{
    if (isAdding) {
        setWindowTitle("Добавить питомца");
        petComboBox->hide(); // Скрываем выбор при добавлении
    } else {
        setWindowTitle("Редактировать питомца");
        petComboBox->show(); // Показываем выбор при редактировании
    }
}
