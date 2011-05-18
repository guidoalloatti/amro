#include "privilegemapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("id, name, description");

PrivilegeMapper::PrivilegeMapper()
{
    this->tableName = "privileges";
}

QList <Privilege> PrivilegeMapper::makePrivileges(QSqlQuery &q)
{
        QList <Privilege> ps;

        q.exec();

        while (q.next())
        {
            Privilege p;


            p.id = q.value(0).toUInt();
            p.name = q.value(1).toString();
            p.description = q.value(2).toString();

            ps << p;
        }

        return ps;
}

bool PrivilegeMapper::insert(const Privilege &p)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :name, :description").
            prepare();

    q.bindValue(":name", p.getName());
    q.bindValue(":description", p.getDescription());

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool PrivilegeMapper::erase(const Privilege &p)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", p.getId());

    return q.exec();
}

bool PrivilegeMapper::update(const Privilege &p)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("name = :name, description = :description").
            Where("id = :id").
            prepare();

    q.bindValue(":id", p.getId());
    q.bindValue(":name", p.getName());
    q.bindValue(":description", p.getDescription());

    return q.exec();
}

QList <Privilege> PrivilegeMapper::get()
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      prepare();

    return makePrivileges(query);
}

QList <Privilege> PrivilegeMapper::get(quint32 id)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", id);

    return makePrivileges(query);
}

QList <Privilege> PrivilegeMapper::get(const QString &name)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("name = :name").
                      prepare();

    query.bindValue(":name", name);

    return makePrivileges(query);
}
