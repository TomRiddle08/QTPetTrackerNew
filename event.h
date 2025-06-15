#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>

class Event {
public:
    enum class Type {
        Feeding,
        Vaccination,
        Grooming,
        Walk,
        VisitToVet,
        Training,
        Other
    };

    Event(const QString& petName, const QString& description, const QDateTime& dateTime, Type type);

    QString getPetName() const;
    QString getDescription() const;
    QDateTime getDateTime() const;
    QString getTypeString() const;
    Type getType() const;

private:
    QString petName;
    QString description;
    QDateTime dateTime;
    Type type;
};

#endif // EVENT_H
