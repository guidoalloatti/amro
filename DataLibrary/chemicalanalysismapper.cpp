#include "chemicalanalysismapper.h"

#include "materialmapper.h"

#include "database.h"
#include <QtSql>

static const QString selectFields("numprobeta, material_id, date, chemicalanalysis");

ChemicalAnalysisMapper::ChemicalAnalysisMapper()
{
    this->tableName = "chemicalanalysis";
}

QList <ChemicalAnalysis> ChemicalAnalysisMapper::makeChemicalAnalysis(QSqlQuery &q)
{
        QList <ChemicalAnalysis> cas;

        q.exec();

        while (q.next())
        {
            ChemicalAnalysis ca;

            ca.numProbeta = q.value(0).toString();

            QList <Material> materials = MaterialMapper().get(q.value(1).toUInt());
            if (materials.length() == 1)
                ca.material = materials.first();
            else
                continue;

            ca.date = q.value(2).toDate();

            QDataStream cds(QByteArray().fromPercentEncoding(q.value(3).toByteArray()));
            QVariantHash chemicalData;
            cds >> chemicalData;

            ChemicalMeasure cMeasure(chemicalData);

            ca.measures = cMeasure;

            cas << ca;
        }

        return cas;
}

bool ChemicalAnalysisMapper::insert(const ChemicalAnalysis &ca)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values(":numprobeta, :material_id, :date, :chemicalanalysis").
            prepare();

    QByteArray serializedCAnalysis;
    QDataStream cas(&serializedCAnalysis, QIODevice::WriteOnly);

    cas << ca.measures.print();

    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":numprobeta", ca.getNumProbeta());
    q.bindValue(":material_id", ca.getMaterial().getId());
    q.bindValue(":date", ca.getDate());

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool ChemicalAnalysisMapper::erase(const ChemicalAnalysis &ca)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("numprobeta = :numprobeta").
            prepare();

    q.bindValue(":numprobeta", ca.getNumProbeta());

    return q.exec();
}

bool ChemicalAnalysisMapper::update(const ChemicalAnalysis &ca)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("material_id = :material_id, date = :date, chemicalanalysis = :chemicalanalysis").
            Where("numprobeta = :numprobeta").
            prepare();

    QByteArray serializedCAnalysis;
    QDataStream cas(&serializedCAnalysis, QIODevice::WriteOnly);

    cas << ca.measures.print();

    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":numprobeta", ca.getNumProbeta());
    q.bindValue(":material_id", ca.getMaterial().getId());
    q.bindValue(":date", ca.getDate());

    return q.exec();
}


QList <ChemicalAnalysis> ChemicalAnalysisMapper::get(QVariantHash filters)
{
    Query queryObject = Query().
                        Select(selectFields).
                        From(tableName);

    foreach(QString key, filters.keys()) {
        if (!selectFields.contains(key))
            return QList<ChemicalAnalysis>();

        queryObject.Where(key + " = :" + key);
    }

    QSqlQuery query = queryObject.prepare();

    foreach(QString key, filters.keys())
        query.bindValue(":" + key, filters.value(key));

    return makeChemicalAnalysis(query);
}
