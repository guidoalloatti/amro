#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

#include "response.h"

class ClientResponse : public Response
{
    QString method;

    static void newClient(JSONP &output, const QHash <QString, QString> &params);
    static void deleteClient(JSONP &output, const QHash <QString, QString> &params);
    static void updateClient(JSONP &output, const QHash <QString, QString> &params);
    static void getClient(JSONP &output, const QHash <QString, QString> &params);

public:
    ClientResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // CLIENTRESPONSE_H
