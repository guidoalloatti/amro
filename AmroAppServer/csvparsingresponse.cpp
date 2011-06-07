#include "csvparsingresponse.h"
#include "../DataLibrary/clientmapper.h"
#include "../DataLibrary/usermapper.h"
#include "../DataLibrary/materialmapper.h"
#include "../DataLibrary/csvparsinglinemapper.h"
#include "../DataLibrary/clientcodemapper.h"

static QString client_relative_path = "../AmroClient/";

CSVParsingResponse::CSVParsingResponse()
{
    methodTable["ParseCSV"] = &CSVParsingResponse::parseCSV;
    methodTable["DeleteOC"] = &CSVParsingResponse::deleteOC;
    methodTable["NewOC"] = &CSVParsingResponse::newOC;
    methodTable["GetOC"] = &CSVParsingResponse::getOC;
}

static bool hasPermission(QString email, QString password, QString permission)
{
    QList <User> users = UserMapper().get(email, password);

    if (users.empty())
        return false;

    return users[0].hasPrivileges(permission);
}

static const QStringList columns = QStringList() << "colada" << "compra" << "descrip" << "material" << "cliente";

static bool parseLines(QFile *file, QVariantHash &error)
{
    QTextStream stream (file);
    QString line;
    int lineNumber = 0;
    QHash <QString, int> headerIndexMapper;
    QString lastNumProbeta;
    QString lastOrdenCompra;
    QString lastMaterial;

    while(!stream.atEnd()) {
        line = stream.readLine();

        QStringList fields;
        fields = line.split(';');

        lineNumber++;
        /* Primero leo el header para saber qué campo corresponderá a su
           homólogo en la base de datos*/
        if (lineNumber == 1) {
            int index = 0, columnsMatched = 0;
            foreach(QString field, fields) {
                foreach (QString property, columns) {
                    if (field.contains(property, Qt::CaseInsensitive)) {
                        headerIndexMapper[property.toLower()] = index;
                        columnsMatched++;
                        break;
                    }
                }
                index++;
            }

            /*if (columns.length() != columnsMatched) {
                error[QString::number(lineNumber)] = "Information incomplete";
                return false;
            }*/
            if (headerIndexMapper.value("colada", -1) == -1 ||
                headerIndexMapper.value("compra", -1) == -1 ||
                headerIndexMapper.value("material", -1) == -1) {
                error[QString::number(lineNumber)] = "Los titulos de cada columna no especifican correctament su contenido";
                return false;
            }

            continue;
        }

        /* A partir de la segunda línea, son todos objectos CSVParsingLine */

        CSVParsingLine pl;

        QList <Material> materials;
        QString material = fields.at(headerIndexMapper["material"]);
        if (material.isEmpty() && !lastMaterial.isEmpty())
            material = lastMaterial;
        else
            lastMaterial = material;
        materials = MaterialMapper().get(material);
        if (materials.length() == 1)
            pl.setMaterial(materials.first());
        else {
            error[QString::number(lineNumber)] = "Material Unknown";
            continue;
        }

        QList <Client> clients;
        int cIndex = headerIndexMapper.value("cliente", -1);
        if (cIndex != -1) {
            clients = ClientMapper().get(fields.at(cIndex));
            if (clients.length() == 1)
                pl.setClient(clients.first());
            else
                error[QString::number(lineNumber)] = "Client Unknown";
        }

        QString probeta = fields.at(headerIndexMapper["colada"]);
        QRegExp numProbetaFormat("([a-z|A-Z]+)(\\s*|\\-)(\\d+)");

        if (numProbetaFormat.exactMatch(probeta)) {
            QString matched = numProbetaFormat.cap(1).toLower() + numProbetaFormat.cap(3);
            pl.setNumProbeta(matched);
            lastNumProbeta = matched;
        } else if (probeta.isEmpty() && !lastNumProbeta.isEmpty())
            pl.setNumProbeta(lastNumProbeta);
        else {
            error[QString::number(lineNumber)] = "Wrong Probeta Format";
            continue;
        }

        QString orden = fields.at(headerIndexMapper["compra"]);

        if (orden.isEmpty() && !lastOrdenCompra.isEmpty())
            orden = lastOrdenCompra;
        else
            lastOrdenCompra = orden;
        pl.setOrdenCompra(orden.toUInt());

        if (headerIndexMapper.value("descrip", -1) != -1) {
            pl.setDescription(fields.at(headerIndexMapper["descrip"]));
        } else
            pl.setDescription("");

        if (!CSVParsingLineMapper().insert(pl))
            error[QString::number(lineNumber)] = "Insert Error";
    }

    return true;
}

void CSVParsingResponse::parseCSV(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "ParseCSV");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    qDebug() << params.value("filepath", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "PARSE_CSV")) {
        QString filePath = params.value("filepath", "").toUtf8();

        QFile csvFile;

        csvFile.setFileName(client_relative_path + filePath);
        if (csvFile.open(QFile::ReadOnly)) {
            QVariantHash error;
            if (parseLines(&csvFile, error))
                success = true;
            output.add("errors", error);
            csvFile.close();
        } else
            output.add("filepath", "failed");

    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void CSVParsingResponse::deleteOC(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteOC");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "OC_DELETE"))
    {
        quint32 id = params.value("id", "").toUInt();

        CSVParsingLine pl;
        pl.setId(id);
        success = CSVParsingLineMapper().erase(pl);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void CSVParsingResponse::newOC(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "NewOC");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "OC_INSERT"))
    {
        CSVParsingLine pl;

        QList <Material> materials = MaterialMapper().get(params.value("material_id", "").toUInt());
        if (materials.length() == 1)
            pl.setMaterial(materials.first());
        else {
            output.add("material", "Material does not exist");
            output.add("success", false);
            return;
        }

        QList <Client> clients = ClientMapper().get(params.value("client_id", "").toUInt());
        if (clients.length() == 1)
            pl.setClient(clients.first());
        else {
            output.add("client", "Client does not exist");
            output.add("success", false);
            return;
        }

        pl.setDescription(params.value("description", "").toUtf8());

        QRegExp numProbetaFormat("([a-z|A-Z]+)(\\s*|\\-)(\\d+)");
        QString numprobeta = params.value("numprobeta", "").toUtf8();
        if (numprobeta.isEmpty() || !numProbetaFormat.exactMatch(numprobeta)) {
            output.add("probeta", "Bad formatted num probeta");
            output.add("success", false);
            return;
        }
        pl.setNumProbeta(numprobeta);

        quint64 orden = params.value("ordencompra", "0").toUInt();
        pl.setOrdenCompra(orden);

        success = CSVParsingLineMapper().insert(pl);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

QVariantList serializeCSVLines(QList <CSVParsingLine> lines)
{
    QVariantList serializedLines;

    foreach(CSVParsingLine pl, lines) {
        QVariantHash linesProperties;

        linesProperties["id"] = pl.getId();
        linesProperties["numprobeta"] = pl.getNumProbeta();
        linesProperties["ordencompra"] = pl.getOrdenCompra();
        //linesProperties["client_id"] = pl.getClient().getId();
        if (pl.getClient().getId() != 0)
            linesProperties["client_id"] = pl.getClient().getId();
        else {
            QRegExp numProbetaFormat("([a-z|A-Z]+)(\\s*|\\-)(\\d+)");
            if (numProbetaFormat.exactMatch(pl.getNumProbeta())) {
                QString matched = numProbetaFormat.cap(1);
                QList <Client> clients = ClientCodeMapper().getClients(matched);
                if (clients.length() != 1)
                    linesProperties["client_id"] = 0;
                else
                    linesProperties["client_id"] = clients.first().getId();
            }
        }

        linesProperties["material_id"] = pl.getMaterial().getId();
        linesProperties["description"] = pl.getDescription().replace('"', "''");

        serializedLines << linesProperties;
    }

    return serializedLines;
}

void CSVParsingResponse::getOC(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "GetOC");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "GET_OC")) {
        QList <CSVParsingLine> lines;
        QVariantHash filters;

        foreach (QString key, params.keys())
            if (key == "numprobeta" && !params[key].isEmpty())
                filters[key] = params.value(key);
            else if (key == "material_id" || key == "client_id" || key == "ordencompra" || key == "id")
                if (!params[key].isEmpty())
                    filters[key] = params.value(key).toUInt();

        QString order = params.value("order", "").toUtf8();
        lines = CSVParsingLineMapper().get(filters, order);

        success = true;
        output.add("lines", serializeCSVLines(lines));
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void CSVParsingResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
