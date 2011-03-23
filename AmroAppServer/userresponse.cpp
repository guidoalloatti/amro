#include "userresponse.h"

UserResponse::UserResponse()
{
    methodTable["Login"] = &UserResponse::login;
    methodTable["NewUser"] = &UserResponse::newUser;
    methodTable["DeleteUser"] = &UserResponse::deleteUser;
    methodTable["UpdateUser"] = &UserResponse::updateUser;
    methodTable["GetUser"] = &UserResponse::getUser;

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
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}

