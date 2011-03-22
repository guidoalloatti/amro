#include "user.h"

User::User(quint32 id, QString name, QString email, QString password, QList <Privilege> privileges, QString signature)
{
    this->id = id;
    this->name = name;
    this->setPassword(password);
    this->setEmail(email);
    this->privileges = privileges;
    this->setSignature(signature);
}

void User::setPassword(QString password)
{
    this->password = password;
}

void User::setEmail(QString email)
{
    this->email = email;
}

void User::setSignature(QString signature)
{
    this->signature = signature;
}

quint32 User::getId() const
{
    return this->id;
}

QString User::getName() const
{
    return this->name;
}

QString User::getPassword() const
{
    return this->password;
}

QString User::getEmail() const
{
    return this->email;
}

QString User::getSignature() const
{
    return this->signature;
}

QList <Privilege> User::getPrivileges() const
{
    return this->privileges;
}

