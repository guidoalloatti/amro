#include "clientresponse.h"
#include "../DataLibrary/clientmapper.h"
#include "../DataLibrary/usermapper.h"
#include "../DataLibrary/clientcodemapper.h"


ClientResponse::ClientResponse()
{
    methodTable["NewClient"] = &ClientResponse::newClient;
    methodTable["DeleteClient"] = &ClientResponse::deleteClient;
    methodTable["UpdateClient"] = &ClientResponse::updateClient;
    methodTable["GetClient"] = &ClientResponse::getClient;
}

static bool hasPermission(QString email, QString password, QString permission)
{
    QList <User> users = UserMapper().get(email, password);

    if (users.empty())
        return false;

    return users[0].hasPrivileges(permission);
}

/* Nombre del cliente debe ser UNIQUE */

void ClientResponse::newClient(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "NewClient");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "CLIENT_INSERT"))
    {
        Client c;
        c.setName(params.value("name", "").toUtf8());
        c.setAddress(params.value("address", "").toUtf8());
        c.setCity(params.value("city", "").toUtf8());
        c.setZip(params.value("zip", "").toUtf8());
        c.setCountry(params.value("country", "").toUtf8());
        c.setPhone(params.value("phone", "").toUtf8());
        c.setWebsite(params.value("website", "").toUtf8());
        c.setTelefax(params.value("telefax", "").toUtf8());
        c.setSequenceDigits(params.value("seqdigits", "").toUInt());

        QString code = params.value("code", "").toUtf8();
        c.setCurrentNameCode(code);

        QList <Client> clients = ClientCodeMapper().getClients(code);
        if (!clients.isEmpty()) {
            output.add("code", code);
        } else
            success = ClientMapper().insert(c);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void ClientResponse::deleteClient(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteClient");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "CLIENT_DELETE"))
    {
        quint32 id = params.value("id", "").toUInt();
        QString name = params.value("name", "").toUtf8();

        Client c(id, name);
        success = ClientMapper().erase(c);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void ClientResponse::updateClient(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "UpdateClient");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "CLIENT_UPDATE"))
    {
        Client c;
        c.setId(params.value("id", "").toUInt());
        c.setName(params.value("name", "").toUtf8());
        c.setAddress(params.value("address", "").toUtf8());
        c.setCity(params.value("city", "").toUtf8());
        c.setZip(params.value("zip", "").toUtf8());
        c.setCountry(params.value("country", "").toUtf8());
        c.setPhone(params.value("phone", "").toUtf8());
        c.setWebsite(params.value("website", "").toUtf8());
        c.setTelefax(params.value("telefax", "").toUtf8());
        c.setSequenceDigits(params.value("seqdigits", "").toUInt());

        QString code = params.value("code", "").toUtf8();

        if (!code.isEmpty()) {
            QList <Client> clients = ClientCodeMapper().getClients(code);
            if (!clients.isEmpty())     {
                if (clients.first().getId() != c.getId()) {
                    output.add("code", code);
                    output.add("success", false);
                    return;
                }
            } else
                c.setCurrentNameCode(code);
        }

        if (c.getCurrentNameCode().isEmpty())
            success = ClientMapper().updateWithoutCode(c);
        else
            success = ClientMapper().updateWithCode(c);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

QVariantList serializeClients(QList <Client> clients)
{
    QVariantList serializedClients;

    foreach(Client c, clients) {
        QVariantHash clientProperties;

        clientProperties["id"] = c.getId();
        clientProperties["name"] = c.getName();
        clientProperties["address"] = c.getAddress();
        clientProperties["city"] = c.getCity();
        clientProperties["country"] = c.getCountry();
        clientProperties["phone"] = c.getPhone();
        clientProperties["telefax"] = c.getTelefax();
        clientProperties["website"] = c.getWebsite();
        clientProperties["code"] = c.getCurrentNameCode();
        clientProperties["zip"] = c.getZip();
        clientProperties["seqdigits"] = c.getSequenceDigits();
        clientProperties["seqnum"] = c.getSequenceNumber();

        QVariantList serializedCodes;
        foreach(QString code, c.getCodeHistory())
            serializedCodes.append(code);

        clientProperties["history"] = serializedCodes;

        serializedClients << clientProperties;
    }

    return serializedClients;
}

void ClientResponse::getClient(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "GetClient");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "CLIENT_LIST")) {
        QList <Client> clients;
        if (params.keys().contains("id"))
            clients = ClientMapper().get(params.value("id").toUInt());
        else
            clients = ClientMapper().get();

        success = true;
        output.add("clients", serializeClients(clients));
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void ClientResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
