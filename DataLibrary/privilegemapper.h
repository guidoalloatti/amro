#ifndef PRIVILEGEMAPPER_H
#define PRIVILEGEMAPPER_H

#include "privilege.h"
#include "query.h"

class DATALIBSHARED_EXPORT PrivilegeMapper
{
    QString tableName;

    QList <Privilege> makePrivileges(QSqlQuery &q);

public:
    PrivilegeMapper();
    bool insert(const Privilege &p);
    bool update(const Privilege &p);
    bool erase(const Privilege &p);
    QList <Privilege> get();
    QList <Privilege> get(quint32 id);
    QList <Privilege> get(const QString &name);

};

#endif // PRIVILEGEMAPPER_H
