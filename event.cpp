#include "event.h"

Event::Event(const QString& petName, const QString& description, const QDateTime& dateTime, Type type)
    : petName(petName), description(description), dateTime(dateTime), type(type) {}

QString Event::getPetName() const {
    return petName;
}

QString Event::getDescription() const {
    return description;
}

QDateTime Event::getDateTime() const {
    return dateTime;
}

QString Event::getTypeString() const {
    switch (type) {
    case Type::Feeding: return "Кормление";
    case Type::Vaccination: return "Прививка";
    case Type::Grooming: return "Груминг";
    case Type::Walk: return "Прогулка";
    case Type::VisitToVet: return "Посещение ветеринара";
    case Type::Training: return "Тренировка";
    default: return "Другое";
    }
}

Event::Type Event::getType() const {
    return type;
}
