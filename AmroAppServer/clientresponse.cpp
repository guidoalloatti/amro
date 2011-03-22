#include "clientresponse.h"

ClientResponse::ClientResponse()
{
    methodTable["NewClient"] = &newClient;
    methodTable["DeleteClient"] = &deleteClient;
    methodTable["UpdateClient"] = &updateClient;
    methodTable["GetClient"] = &getClient;
}

void ClientResponse::login(JSONP &output, const QHash <QString, QString> &params)
{

}

void ClientResponse::newClient(JSONP &output, const QHash <QString, QString> &params)
{

}

void ClientResponse::deleteClient(JSONP &output, const QHash <QString, QString> &params)
{

}

void ClientResponse::updateClient(JSONP &output, const QHash <QString, QString> &params)
{

}

void ClientResponse::getClient(JSONP &output, const QHash <QString, QString> &params)
{

}

void ClientResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, QHash <QString, QString> &) = methodTable.value(method);

    if (f != 0)
        return (*f)(output, params);
}
