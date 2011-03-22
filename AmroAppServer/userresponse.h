#ifndef USERRESPONSE_H
#define USERRESPONSE_H

#include "response.h"

class UserResponse : Response
{
    QString method;

    void login(JSONP &output, const QHash <QString, QString> &params);
    void newUser(JSONP &output, const QHash <QString, QString> &params);
    void deleteUser(JSONP &output, const QHash <QString, QString> &params);
    void updateUser(JSONP &output, const QHash <QString, QString> &params);
    void getUser(JSONP &output, const QHash <QString, QString> &params);

public:
    UserResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // USERRESPONSE_H
