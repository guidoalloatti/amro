#include "user.h"

User::User(quint32 id, QString email, QString password)
{
    this->id = id;
    this->email = email;
    this->setPassword(password);    
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

void User::addPrivilege(Privilege p)
{
    this->privileges.append(p);
}

void User::setSurname(QString surname)
{
    this->surname = surname;
}

void User::setName(QString name)
{
    this->name = name;
}


quint32 User::getId() const
{
    return this->id;
}

QString User::getName() const
{
    return this->name;
}

QString User::getSurname() const
{
    return this->surname;
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

bool User::hasPrivileges(QString privilege)
{
    QList <Privilege> privileges = this->getPrivileges();

    foreach (Privilege p, privileges)
        if (p.getName() == privilege || p.getName() == "ADMIN")
            return true;

    return false;
}
