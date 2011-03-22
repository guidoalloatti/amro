#ifndef USERMAPPER_H
#define USERMAPPER_H

#include "user.h"
#include "query.h"

class DATALIBSHARED_EXPORT UserMapper
{
    QString tableName;

    QList <User> makeUsers(QSqlQuery &q);

public:
    UserMapper();
    bool insert(const User &u);
    bool update(const User &u);
    bool erase(const User &u);
    QList <User> get(quint32 id);
    QList <User> get(const QString &user, const QString &password);
};

#endif // USERMAPPER_H
