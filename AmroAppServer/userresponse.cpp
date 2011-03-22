#include "userresponse.h"

UserResponse::UserResponse()
{
    methodTable["Login"] = &login;
    methodTable["NewUser"] = &newUser;
    methodTable["DeleteUser"] = &deleteUser;
    methodTable["UpdateUser"] = &updateUser;
    methodTable["GetUser"] = &getUser;

}

void UserResponse::login(JSONP &output, const QHash <QString, QString> &params)
{

}

void UserResponse::newUser(JSONP &output, const QHash <QString, QString> &params)
{

}

void UserResponse::deleteUser(JSONP &output, const QHash <QString, QString> &params)
{

}

void UserResponse::updateUser(JSONP &output, const QHash <QString, QString> &params)
{

}

void UserResponse::getUser(JSONP &output, const QHash <QString, QString> &params)
{

}

void UserResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, QHash <QString, QString> &) = methodTable.value(method);

    if (f != 0)
        return (*f)(output, params);
}
