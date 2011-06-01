#ifndef USERRESPONSE_H
#define USERRESPONSE_H

#include "response.h"

class UserResponse : public Response
{
    QString method;

    static void login(JSONP &output, const QHash <QString, QString> &params);
    static void newUser(JSONP &output, const QHash <QString, QString> &params);
    static void deleteUser(JSONP &output, const QHash <QString, QString> &params);
    static void updateUser(JSONP &output, const QHash <QString, QString> &params);
    static void updatePrivileges(JSONP &output, const QHash <QString, QString> &params);
    static void getUser(JSONP &output, const QHash <QString, QString> &params);

public:
    UserResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // USERRESPONSE_H
