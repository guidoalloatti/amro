#include "chemicalanalysismapper.h"

#include "materialmapper.h"
#include "termicaltreatmentmapper.h"

#include "database.h"
#include <QtSql>

static const QString selectFields("id, numprobeta, material_id, date, ttreatment_id, chemicalanalysis");

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

            ca.id = q.value(0).toUInt();

            ca.numProbeta = q.value(1).toString();

            QList <Material> materials = MaterialMapper().get(q.value(2).toUInt());
            if (materials.length() == 1)
                ca.material = materials.first();
            else
                continue;

            ca.date = q.value(3).toDate();

            QList <TermicalTreatment> tts = TermicalTreatmentMapper().get(q.value(4).toUInt());
            if (tts.length() == 1)
                ca.termicalTreatment = tts.first();

            QDataStream cds(QByteArray().fromPercentEncoding(q.value(5).toByteArray()));
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
            Values("DEFAULT, :numprobeta, :material_id, :date, :ttreatment_id, :chemicalanalysis").
            prepare();

    QByteArray serializedCAnalysis;
    QDataStream cas(&serializedCAnalysis, QIODevice::WriteOnly);

    cas << ca.measures.print();

    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":numprobeta", ca.getNumProbeta());
    q.bindValue(":material_id", ca.getMaterial().getId());
    q.bindValue(":date", ca.getDate());
    q.bindValue(":ttreatment_id", ca.GetTermicalTreatment().getId());

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
            Where("id = :id").
            prepare();

    q.bindValue(":id", ca.getId());

    return q.exec();
}

bool ChemicalAnalysisMapper::update(const ChemicalAnalysis &ca)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("material_id = :material_id, date = :date, ttreatment_id = :ttreatment_id, chemicalanalysis = :chemicalanalysis").
            Where("numprobeta = :numprobeta").
            And("id = :id").
            prepare();

    QByteArray serializedCAnalysis;
    QDataStream cas(&serializedCAnalysis, QIODevice::WriteOnly);

    cas << ca.measures.print();

    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":numprobeta", ca.getNumProbeta());
    q.bindValue(":material_id", ca.getMaterial().getId());
    q.bindValue(":date", ca.getDate());
    q.bindValue(":ttreatment_id", ca.GetTermicalTreatment().getId());
    q.bindValue(":id", ca.getId());

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
