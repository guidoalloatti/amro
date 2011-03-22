#include "clientcodemapper.h"
#include "clientmapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("client_id, code");

ClientCodeMapper::ClientCodeMapper()
{
    this->tableName = "clientcodes";
}

static QList <QString> makeClientCodes(QSqlQuery &q)
{
        QList <QString> clientCodes;

        q.exec();

        while (q.next()) {
            QString code;

            code = q.value(1).toString();

            clientCodes << code;
        }

        return clientCodes;
}

static QList <Client> makeClients(QSqlQuery &q)
{
    QList <Client> clients;

    q.exec();

    while (q.next())
    {
        QList <Client> c;

        c = ClientMapper().get(q.value(0).toUInt());

        clients << c;
    }

    return clients;
}


bool ClientCodeMapper::insert(const Client &c, const QString &code)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :client_id, :code").
            prepare();

    QList <QString> codes = ClientCodeMapper().getCodes(c.getId());

    if (codes.contains(code))
        return false;

    q.bindValue(":client_id", c.getId());
    q.bindValue(":code", code);

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool ClientCodeMapper::erase(const Client &c, const QString &code)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("client_id = :client_id").
            And("code = :code").
            prepare();

    q.bindValue(":client_id", c.getId());
    q.bindValue(":code", code);

    return q.exec();
}

QList <QString> ClientCodeMapper::getCodes(quint32 id)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", id);

    return makeClientCodes(query);
}

QList <Client> ClientCodeMapper::getClients(QString &code)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("code = :code").
                      prepare();

    query.bindValue(":code", code);

    return makeClients(query);
}

