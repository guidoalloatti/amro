#include "usermapper.h"
#include "userpermissionsmapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("id, name, surname, email, password, signature");

UserMapper::UserMapper()
{
    this->tableName = "users";
}

QList <User> UserMapper::makeUsers(QSqlQuery &q)
{
        QList <User> users;

        q.exec();

        while (q.next())
        {
            User u;

            u.id = q.value(0).toUInt();
            u.name = q.value(1).toString();
            u.surname = q.value(2).toString();
            u.email = q.value(3).toString();
            u.password = q.value(4).toString();
            u.signature = q.value(5).toString();

            u.privileges = UserPermissionsMapper().getPrivileges(u);

            users << u;
        }

        return users;
}

bool UserMapper::insert(const User &u)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :name, :surname, :password, :email, :signature").
            prepare();

    q.bindValue(":name", u.getName());
    q.bindValue(":surname", u.surname);
    q.bindValue(":password", u.getPassword());
    q.bindValue(":email", u.email);
    q.bindValue(":signature", u.signature);

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool UserMapper::erase(const User &u)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", u.getId());

    return q.exec();
}

bool UserMapper::update(const User &u)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("DEFAULT, :name, :surname, :password, :email, :signature").
            Where("id = :id").
            prepare();

    q.bindValue(":id", u.getId());
    q.bindValue(":name", u.getName());
    q.bindValue(":surname", u.surname);
    q.bindValue(":password", u.getPassword());
    q.bindValue(":email", u.email);
    q.bindValue(":signature", u.signature);

    return q.exec();
}

QList <User> UserMapper::get(quint32 id)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", id);

    return makeUsers(query);
}

QList <User> UserMapper::get(const QString &email, const QString &password)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("email = :email").
                      And("password = :password").
                      prepare();

    query.bindValue(":email", email);
    query.bindValue(":password", password);

    return makeUsers(query);
}

