#ifndef PRIVILEGE_H
#define PRIVILEGE_H

#include "DataLib_global.h"

#include <QString>

class DATALIBSHARED_EXPORT Privilege
{
public:
    Privilege() {}
    Privilege(quint32 id, QString name, QString description);

    quint32 getId() const;
    QString getName() const;
    QString getDescription() const;
    bool operator== (const Privilege &p) {return id == p.id;}

private:
    quint32 id;
    QString name;
    QString description;

    friend class PrivilegeMapper;
};

#endif // PRIVILEGE_H
