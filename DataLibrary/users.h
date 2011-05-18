#ifndef USERS_H
#define USERS_H

#include "DataLib_global.h"

#include <QString>
#include <QList>

#include "device.h"

//! Customer datatype
class DATALIBSHARED_EXPORT Customer
{
public:
    Customer() {}
    Customer(quint32 id, QString name, QString user, QString password, QString email, QList <Device> devices);
    void setPassword(QString password);
    void setEmail(QString email);
    quint32 getId() const;
    QString getName() const;
    QString getUsername() const; // DEPRECATED
    QString getPassword() const;
    QString getEmail() const;
    QList <Device> getDevices() const;

    QList <Device> devices;
    quint32 id;
    QString password, email, name, surname, company, address, city, zip, country, phone, telefax, website;

    friend class CustomerMapper;
};

class Users
{
public:
    Users() {}

    User



};

#endif // USERS_H
