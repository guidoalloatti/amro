#include "userresponse.h"
#include "../DataLibrary/usermapper.h"
#include "../DataLibrary/privilegemapper.h"


UserResponse::UserResponse()
{
    methodTable["Login"] = &UserResponse::login;
    methodTable["NewUser"] = &UserResponse::newUser;
    methodTable["DeleteUser"] = &UserResponse::deleteUser;
    methodTable["UpdateUser"] = &UserResponse::updateUser;
    methodTable["GetUser"] = &UserResponse::getUser;

}

static bool hasPermission(QString email, QString password, QString permission)
{
    QList <User> users = UserMapper().get(email, password);

    if (users.empty())
        return false;

    qDebug() << "Usuario obtenido " + users[0].getName() + "con permisos " << users[0].getPrivileges().length();

    return users[0].hasPrivileges(permission);
}

void UserResponse::login(JSONP &output, const QHash <QString, QString> &params)
{
    UserMapper um;

    qDebug() << "En LOGIN";

    QList <User> users = um.get(params["email"], params["password"]);

    if (users.size() == 1)
        output.add("success", true);
    else
        output.add("success", false);
}

/* Recordar que email está marcado como UNIQUE en la base de datos */

void UserResponse::newUser(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "NewUser");

    User u;
    u.setPassword(params.value("password", "").toUtf8());
    u.setEmail(params.value("email", "").toUtf8());
    u.setName(params.value("name", "").toUtf8());
    u.setSurname(params.value("surname", "").toUtf8());
    u.setSignature(params.value("signature", "").toUtf8());

    foreach(Privilege p, PrivilegeMapper().get()) {
        QString key = p.getName();
        if (params.keys().contains(key))
            u.addPrivilege(p);        
    }

    output.add("success", UserMapper().insert(u));
}

void UserResponse::deleteUser(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteUser");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "USER_DELETE")) {
            User u(params.value("id", "").toUInt(), "", "");
            success = UserMapper().erase(u);
    } else
        output.add("permission", "denied");

    output.add("success", success);
}

void UserResponse::updateUser(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "UpdateUser");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    QList <User> users = UserMapper().get(email, password);

    bool success = true;

    if (!users.empty())
    {
        User u(users[0].getId(), email, password);
        u.setName(params.value("name", "").toUtf8());
        u.setSurname(params.value("surname", "").toUtf8());
        u.setSignature(params.value("signature", "").toUtf8());

        foreach(Privilege p, PrivilegeMapper().get()) {
            QString key = p.getName();
            if (params.keys().contains(key))
                u.addPrivilege(p);
        }

        success = UserMapper().update(u);
    }
    else
        success = false;

    output.add("success", success);
}

QVariantList serializeUsers(QList <User> users)
{
    QVariantList serializedUsers;

    foreach(User u, users) {
        QVariantHash userProperties;

        userProperties["id"] = u.getId();
        userProperties["name"] = u.getName();
        userProperties["surname"] = u.getSurname();
        userProperties["email"] = u.getEmail();
        userProperties["signature"] = u.getSignature();

        QVariantList serializedPrivs;
        foreach(Privilege p, u.getPrivileges())
            serializedPrivs.append(p.getName());

        userProperties["privileges"] = serializedPrivs;

        serializedUsers << userProperties;
    }

    return serializedUsers;
}

void UserResponse::getUser(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "GetUser");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "USER_LIST")) {
        QList <User> users;

        if (params.keys().contains("id"))
            users = UserMapper().get(params.value("id").toUInt());
        else
            users = UserMapper().get();

        success = true;
        output.add("users", serializeUsers(users));
    } else
        output.add("permission", "denied");

    output.add("success", success);
}

void UserResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
