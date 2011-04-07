#include "clientmapper.h"
#include "clientcodemapper.h"

#include "datalib.h"
#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("id, name, address, city, zip, country, phone, telefax, website, namecode, sequencedigits, currentsequence");

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
            c.sequenceDigits = q.value(10).toUInt();
            c.currentSequence = q.value(11).toUInt();

            c.codeHistory = ClientCodeMapper().getCodes(c.id);

            cs << c;
        }

        return cs;
}

bool ClientMapper::insert(Client &c)
{
    if (!DataLib::transaction())
        return false;

    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :name, :address, :city, :zip, :country, :phone, :telefax, :website, :namecode, :sequencedigits").
            prepare();

    q.bindValue(":name", c.getName());
    q.bindValue(":address", c.address);
    q.bindValue(":city", c.city);
    q.bindValue(":zip", c.zip);
    q.bindValue(":country", c.country);
    q.bindValue(":phone", c.phone);
    q.bindValue(":telefax", c.telefax);
    q.bindValue(":website", c.website);
    q.bindValue("namecode", c.nameCode);
    q.bindValue("sequencedigits", c.sequenceDigits);

    bool s = q.exec();

    if (!s) {
        qDebug() << q.lastError() << endl;
        return s;
    }

    QSqlQuery q2 =
            Query().
            Select("LAST_INSERT_ID()").
            prepare();

    s = q2.exec();
    if (!s) {
        DataLib::rollback();
        return false;
    }

    q2.next();
    c.id = q2.value(0).toUInt();

    s = ClientCodeMapper().insert(c, c.getCurrentNameCode());
    if (!s) {
        DataLib::rollback();
        return false;
    }

    return DataLib::commit();
}

bool ClientMapper::erase(const Client &c)
{
    if (!DataLib::transaction())
        return false;

    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", c.getId());

    bool s = q.exec();

    if (!s)
        return false;

    foreach (QString code, ClientCodeMapper().getCodes(c.getId())) {
        s = ClientCodeMapper().erase(c, code);
        if (!s) {
            DataLib::rollback();
            return false;
        }
    }

    return DataLib::commit();
}

bool ClientMapper::update(const Client &c)
{
    if (!DataLib::transaction())
        return false;

    QSqlQuery q =
            Query().
            Update(tableName).
            Set("name = :name, address = :address, city = :city, zip = :zip, country = :country, phone = :phone, telefax = :telefax, website = :website, namecode = :namecode, sequencedigits = :sequencedigits").
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
    q.bindValue("namecode", c.nameCode);
    q.bindValue("sequencedigits", c.sequenceDigits);

    bool s = q.exec();

    if (!s)
        return false;

    QString code = c.getCurrentNameCode();
    if (!code.isEmpty()) {
        s = ClientCodeMapper().insert(c, code);
        if (!s) {
            DataLib::rollback();
            return false;
        }
    }

    return DataLib::commit();
}

QList <Client> ClientMapper::get()
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      prepare();

    return makeClients(query);
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

