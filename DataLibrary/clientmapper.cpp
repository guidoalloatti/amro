#include "clientmapper.h"
#include "clientcodemapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("id, name, address, city, zip, country, phone, telefax, website, namecode, sequencenumber");

ClientMapper::ClientMapper()
{
    this->tableName = "clients";
}

QList <Client> ClientMapper::makeClients(QSqlQuery &q)
{
        QList <Client> cs;

        q.exec();

        while (q.next())
        {
            Client c;

            c.id = q.value(0).toUInt();
            c.name = q.value(1).toString();
            c.address = q.value(2).toString();
            c.city = q.value(3).toString();
            c.zip = q.value(4).toString();
            c.country = q.value(5).toString();
            c.phone = q.value(6).toString();
            c.telefax = q.value(7).toString();
            c.website = q.value(8).toString();
            c.nameCode = q.value(9).toString();
            c.sequenceNumber = q.value(10).toString();

            c.codeHistory = ClientCodeMapper().getCodes(c.id);

            cs << c;
        }

        return cs;
}

bool ClientMapper::insert(const Client &c)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :name, :address, :city, :zip, :country, :phone, :telefax, :website").
            prepare();

    q.bindValue(":name", c.getName());
    q.bindValue(":address", c.address);
    q.bindValue(":city", c.city);
    q.bindValue(":zip", c.zip);
    q.bindValue(":country", c.country);
    q.bindValue(":phone", c.phone);
    q.bindValue(":telefax", c.telefax);
    q.bindValue(":website", c.website);

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool ClientMapper::erase(const Client &c)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", c.getId());

    return q.exec();
}

bool ClientMapper::update(const Client &c)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("DEFAULT, :name, :address, :city, :zip, :country, :phone, :telefax, :website").
            Where("id = :id").
            prepare();

    q.bindValue(":id", c.getId());
    q.bindValue(":name", c.getName());
    q.bindValue(":address", c.address);
    q.bindValue(":city", c.city);
    q.bindValue(":zip", c.zip);
    q.bindValue(":country", c.country);
    q.bindValue(":phone", c.phone);
    q.bindValue(":telefax", c.telefax);
    q.bindValue(":website", c.website);

    return q.exec();
}


QList <Client> ClientMapper::get(quint32 id)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", id);

    return makeClients(query);
}

QList <Client> ClientMapper::get(const QString &name)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("name = :name").
                      prepare();

    query.bindValue(":name", name);

    return makeClients(query);
}

