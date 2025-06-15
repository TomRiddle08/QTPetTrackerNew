#ifndef PET_H
#define PET_H

#include <QString>

class Pet {
public:
    explicit Pet(const QString& name,
                 const QString& owner,
                 const QString& breed,
                 int age,
                 double weight = 0.0,
                 const QString& color = "",
                 const QString& description = "");

    void setName(const QString& name);
    void setOwner(const QString& owner);
    void setBreed(const QString& breed);
    void setAge(int age);
    void setWeight(double weight);
    void setColor(const QString& color);
    void setDescription(const QString& description);

    QString getName() const;
    QString getOwner() const;
    QString getBreed() const;
    int getAge() const;
    double getWeight() const;
    QString getColor() const;
    QString getDescription() const;

private:
    QString name;
    QString owner;
    QString breed;
    int age;
    double weight;
    QString color;
    QString description;
};

#endif // PET_H
