#include "pet.h"

Pet::Pet(const QString& name, const QString& owner, const QString& breed, int age, double weight, const QString& color, const QString& description)
    : name(name), owner(owner), breed(breed), age(age), weight(weight), color(color), description(description) {}

void Pet::setName(const QString& name) {
    this->name = name;
}

void Pet::setOwner(const QString& owner) {
    this->owner = owner;
}

void Pet::setBreed(const QString& breed) {
    this->breed = breed;
}

void Pet::setAge(int age) {
    this->age = age;
}

void Pet::setWeight(double weight) {
    this->weight = weight;
}

void Pet::setColor(const QString& color) {
    this->color = color;
}

void Pet::setDescription(const QString& description) {
    this->description = description;
}

QString Pet::getName() const {
    return name;
}

QString Pet::getOwner() const {
    return owner;
}

QString Pet::getBreed() const {
    return breed;
}

int Pet::getAge() const {
    return age;
}

double Pet::getWeight() const {
    return weight;
}

QString Pet::getColor() const {
    return color;
}

QString Pet::getDescription() const {
    return description;
}
