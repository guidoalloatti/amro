#include "clientresponse.h"

ClientResponse::ClientResponse()
{
    methodTable["NewClient"] = &ClientResponse::newClient;
    methodTable["DeleteClient"] = &ClientResponse::deleteClient;
    methodTable["UpdateClient"] = &ClientResponse::updateClient;
    methodTable["GetClient"] = &ClientResponse::getClient;
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
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
