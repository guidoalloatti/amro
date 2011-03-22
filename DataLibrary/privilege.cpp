#include "privilege.h"

Privilege::Privilege(quint32 id, QString name, QString description)
{
    this->id = id;
    this->name = name;
    this->description = description;
}

quint32 Privilege::getId() const
{
    return this->id;
}

QString Privilege::getName() const
{
    return this->name;
}

QString Privilege::getDescription() const
{
    return this->description;
}

