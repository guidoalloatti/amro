#include "userpermissionsmapper.h"

#include "usermapper.h"
#include "privilegemapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("user_id, permission_id");

UserPermissionsMapper::UserPermissionsMapper()
{
    this->tableName = "userpermissions";
}

static QList <User> makeUsers(QSqlQuery &q)
{
        QList <User> users;

        q.exec();

        while (q.next())
        {
            QList <User> privUsers;

            privUsers = UserMapper().get(q.value(0).toUInt());

            // Debo crear pero que no se repitan!!!!
            foreach(User u, privUsers)
                if (!users.contains(u))
                    users << u;
        }

        return users;
}

static QList <Privilege> makePrivileges(QSqlQuery &q)
{
    QList <Privilege> pvs;

    q.exec();

    while (q.next())
    {
        QList <Privilege> userPrivs;

        userPrivs = PrivilegeMapper().get(q.value(1).toUInt());

        // Debo crear pero que no se repitan!!!!
        foreach(Privilege p, userPrivs)
            if (!pvs.contains(p))
                pvs << p;
    }

    return pvs;
}


bool UserPermissionsMapper::insert(const User &u, const Privilege &p)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :user_id, :privilege_id").
            prepare();

    if (u.getPrivileges().contains(p))
        return false;

    q.bindValue(":user_id", u.getId());
    q.bindValue(":privilege_id", p.getId());

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool UserPermissionsMapper::erase(const User &u, const Privilege &p)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("user_id = :user_id").
            And("privilege_id = :privilege_id").
            prepare();

    if (u.getPrivileges().contains(p))
        return false;

    q.bindValue(":user_id", u.getId());
    q.bindValue(":privilege_id", p.getId());

    return q.exec();
}

bool  UserPermissionsMapper::update(const User &u, const Privilege &p)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("DEFAULT, :user_id, :privilege_id").
            Where("user_id = :user_id").
            prepare();

    q.bindValue(":user_id", u.getId());
    q.bindValue(":privilege_id", p.getId());

    return q.exec();
}

QList <Privilege>  UserPermissionsMapper::getPrivileges(const User &u)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", u.getId());

    return makePrivileges(query);
}

QList <User> UserPermissionsMapper::getUsers(const Privilege &p)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", p.getId());

    return makeUsers(query);
}
