#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

#include "response.h"

class ClientResponse : Response
{
    QString method;

    void newClient(JSONP &output, const QHash <QString, QString> &params);
    void deleteClient(JSONP &output, const QHash <QString, QString> &params);
    void updateClient(JSONP &output, const QHash <QString, QString> &params);
    void getClient(JSONP &output, const QHash <QString, QString> &params);

public:
    ClientResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // CLIENTRESPONSE_H
