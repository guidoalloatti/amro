#ifndef USERPERMISSIONSMAPPER_H
#define USERPERMISSIONSMAPPER_H

#include "user.h"
#include "privilege.h"

class DATALIBSHARED_EXPORT UserPermissionsMapper
{
    QString tableName;

public:
    UserPermissionsMapper();
    bool insert(const User &u, const Privilege &p);
    bool update(const User &u, const Privilege &p);
    bool erase(const User &u, const Privilege &p);
    QList <User> getUsers(const Privilege &p);
    QList <Privilege> getPrivileges(const User &u);

};

#endif // USERPERMISSIONSMAPPER_H
