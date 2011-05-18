#ifndef CLIENTCODEMAPPER_H
#define CLIENTCODEMAPPER_H

#include "client.h"

class DATALIBSHARED_EXPORT ClientCodeMapper
{
    QString tableName;

public:
    ClientCodeMapper();
    bool insert(const Client &c, const QString &code);
    //bool update(const Client &c, const QString &code);
    bool erase(const Client &c, const QString &code);
    QList <QString> getCodes(quint32);
    QList <Client> getClients(QString &code);

};

#endif // CLIENTCODEMAPPER_H
