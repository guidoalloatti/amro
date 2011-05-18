#include "csvparsinglinemapper.h"

#include "clientmapper.h"
#include "materialmapper.h"

#include "database.h"
#include <QtSql>

static const QString selectFields("id, numprobeta, ordencompra, material_id, client_id, description");

CSVParsingLineMapper::CSVParsingLineMapper()
{
    this->tableName = "csvparsing";
}

QList <CSVParsingLine> CSVParsingLineMapper::makeCSVParsingLines(QSqlQuery &q)
{
        QList <CSVParsingLine> pls;

        q.exec();

        while (q.next())
        {
            CSVParsingLine pl;

            pl.id = q.value(0).toUInt();
            pl.numProbeta = q.value(1).toString();
            pl.ordenCompra = q.value(2).toUInt();

            QList <Material> materials = MaterialMapper().get(q.value(3).toUInt());
            if (materials.length() == 1)
                pl.material = materials.first();
            else
                continue;

            if (q.value(4) != 0) {
                QList <Client> clients = ClientMapper().get(q.value(4).toUInt());
                if (clients.length() == 1)
                    pl.client = clients.first();
                else
                    continue;
            } else
                pl.client.setId(0);

            pl.description = q.value(5).toString();

            pls << pl;
        }

        return pls;
}

bool CSVParsingLineMapper::insert(const CSVParsingLine &pl)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :numprobeta, :ordencompra, :material_id, :client_id, :description").
            prepare();

    q.bindValue(":numprobeta", pl.getNumProbeta());
    q.bindValue("client_id", pl.getClient().getId());
    q.bindValue(":material_id", pl.getMaterial().getId());
    q.bindValue(":ordencompra", pl.getOrdenCompra());
    q.bindValue(":description", pl.getDescription());

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}


bool CSVParsingLineMapper::erase(const CSVParsingLine &pl)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", pl.getId());

    return q.exec();
}

bool CSVParsingLineMapper::update(const CSVParsingLine &pl)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("ordencompra = :ordencompra, material_id = :material_id, client_id = :client_id, description = :description").
            Where("numprobeta = :numprobeta").
            And("id = :id").
            prepare();

    q.bindValue(":numprobeta", pl.getNumProbeta());
    q.bindValue("client_id", pl.getClient().getId());
    q.bindValue(":material_id", pl.getMaterial().getId());
    q.bindValue(":ordencompra", pl.getOrdenCompra());
    q.bindValue(":description", pl.getDescription());
    q.bindValue(":id", pl.getId());

    return q.exec();
}


QList <CSVParsingLine> CSVParsingLineMapper::get(QVariantHash filters, QString order)
{
    Query queryObject = Query().
                        Select(selectFields).
                        From(tableName).
                        OrderBy(order);

    foreach(QString key, filters.keys()) {
        if (!selectFields.contains(key))
            return QList<CSVParsingLine>();

        queryObject.Where(key + " = :" + key);
    }

    QSqlQuery query = queryObject.prepare();

    foreach(QString key, filters.keys())
        query.bindValue(":" + key, filters.value(key));

    return makeCSVParsingLines(query);
}


