#ifndef USER_H
#define USER_H

#include "DataLib_global.h"

#include <QString>
#include <QList>

#include "privilege.h"

class DATALIBSHARED_EXPORT User
{
public:
    User() {}
    User(quint32 id, QString email, QString password);

    void setPassword(QString password);
    void setEmail(QString email);
    void setSignature(QString signature);
    void addPrivilege(Privilege p);
    void setSurname(QString surname);
    void setName(QString name);

    quint32 getId() const;
    QString getName() const;
    QString getSurname() const;
    QString getPassword() const;
    QString getEmail() const;
    QString getSignature() const;
    QList <Privilege> getPrivileges() const;
    bool operator== (const User &s1) {return id == s1.id;}

    bool hasPrivileges(QString privilege);

private:
    QList <Privilege> privileges;
    quint32 id;
    QString password, email, name, surname, signature;

    friend class UserMapper;
};

#endif // USER_H
