#include "userresponse.h"

#include <QDir>

#include "../DataLibrary/usermapper.h"
#include "../DataLibrary/privilegemapper.h"

static QString default_privileges = "USER_LIST, CLIENT_LIST, MATERIAL_LIST, CERTIFICATE_LIST, GET_CA, GET_OC, TT_LIST, GET_MA";
static QString relative_user_folder = "../AmroClient/certificados/img/";

UserResponse::UserResponse()
{
    methodTable["Login"] = &UserResponse::login;
    methodTable["NewUser"] = &UserResponse::newUser;
    methodTable["DeleteUser"] = &UserResponse::deleteUser;
    methodTable["UpdateUser"] = &UserResponse::updateUser;
    methodTable["GetUser"] = &UserResponse::getUser;
    methodTable["UpdatePrivileges"] = &UserResponse::updatePrivileges;

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
        if (default_privileges.contains(key))
            u.addPrivilege(p);
    }    

    bool success = UserMapper().insert(u);

    if (success) {
        QDir dir;
        success = dir.mkdir(relative_user_folder + QString::number(u.getId()));
        if (!success)
            UserMapper().erase(u);
        else {
            QFile file(relative_user_folder + QString::number(u.getId()));
            file.setPermissions(file.permissions() | QFile::WriteGroup | QFile::WriteOther);
        }
    }

    output.add("success", success);
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

    QString from_email = params.value("from_email", "").toUtf8();
    QString from_password = params.value("from_password", "").toUtf8();

    QList <User> users = UserMapper().get(params.value("user_id", "0").toUInt());
    if (users.length() != 1) {
        output.add("error", "User does not exists");
        output.add("success", false);
        return;
    }

    User u = users.first();

    bool success = false;

    if ((u.getEmail() == from_email && u.getPassword() == from_password)||
        hasPermission(from_email, from_password, "USER_UPDATE")) {

        QString name = params.value("name", "").toUtf8();
        if (!name.isEmpty())
            u.setName(name);

        QString surname = params.value("surname", "").toUtf8();
        if (!surname.isEmpty())
            u.setSurname(params.value("surname", "").toUtf8());

        QString signature = params.value("signature", "").toUtf8();
        if (!signature.isEmpty())
            u.setSignature(params.value("signature", "").toUtf8());

        QString email = params.value("email", "").toUtf8();
        if (!email.isEmpty())
            u.setEmail(params.value("email", "").toUtf8());

        QString password = params.value("password", "").toUtf8();
        if (!password.isEmpty())
            u.setPassword(params.value("password", "").toUtf8());

        success = UserMapper().update(u);
    }
    else
        success = false;

    output.add("success", success);
}

void UserResponse::updatePrivileges(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "UpdatePrivileges");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "USER_UPDATE")) {
        QList <User> users = UserMapper().get(params.value("user_id", "0").toUInt());
        if (users.length() != 1) {
            output.add("error", "User does not exists");
            output.add("success", false);
            return;
        }

        User u = users.first();

        QString denied;

        foreach(Privilege p, PrivilegeMapper().get()) {
            QString key = p.getName();
            if (params.value("privileges", "").contains(key) && !u.getPrivileges().contains(p)) {
                if (hasPermission(email, password, key))
                    u.addPrivilege(p);
                else
                    denied.append(key + " ");
            }
        }

        output.add("denied", denied);

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
