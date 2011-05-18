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
    bool insert(Client &c);
    bool updateWithoutCode(const Client &c);
    bool updateWithCode(const Client &c);
    bool erase(const Client &c);
    QList <Client> get();
    QList <Client> get(quint32 id);
    QList <Client> get(const QString &name);

};

#endif // CLIENTMAPPER_H
