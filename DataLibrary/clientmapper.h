#ifndef CLIENTMAPPER_H
#define CLIENTMAPPER_H

#include "client.h"
#include "query.h"

class DATALIBSHARED_EXPORT ClientMapper
{
    QString tableName;

    QList <Client> makeClients(QSqlQuery &q);

public:
    ClientMapper();
    bool insert(const Client &c);
    bool update(const Client &c);
    bool erase(const Client &c);
    QList <Client> get(quint32 id);
    QList <Client> get(const QString &name);

};

#endif // CLIENTMAPPER_H
