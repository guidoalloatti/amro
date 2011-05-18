#include "mechanicalanalysismapper.h"

#include "materialmapper.h"

#include "database.h"
#include <QtSql>

static const QString selectFields("id, material_id, date, mechanicalanalysis");

MechanicalAnalysisMapper::MechanicalAnalysisMapper()
{
    this->tableName = "mechanicalanalysis";
}

QList <MechanicalAnalysis> MechanicalAnalysisMapper::makeMechanicalAnalysis(QSqlQuery &q)
{
        QList <MechanicalAnalysis> mas;

        q.exec();

        while (q.next())
        {
            MechanicalAnalysis ma;

            ma.setId(q.value(0).toUInt());

            QList <Material> materials = MaterialMapper().get(q.value(1).toUInt());
            if (materials.length() == 1)
                ma.material = materials.first();
            else
                continue;

            ma.date = q.value(2).toDate();

            QDataStream mds(QByteArray().fromPercentEncoding(q.value(3).toByteArray()));
            QVariantHash MechanicalData;
            mds >> MechanicalData;

            MechanicalMeasure mMeasure(MechanicalData);

            ma.measures = mMeasure;

            mas << ma;
        }

        return mas;
}

bool MechanicalAnalysisMapper::insert(const MechanicalAnalysis &ma)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :material_id, :date, :mechanicalanalysis").
            prepare();

    QByteArray serializedMAnalysis;
    QDataStream mas(&serializedMAnalysis, QIODevice::WriteOnly);

    mas << ma.measures.print();

    q.bindValue(":mechanicalanalysis", serializedMAnalysis.toPercentEncoding());
    q.bindValue(":material_id", ma.getMaterial().getId());
    q.bindValue(":date", ma.getDate());

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool MechanicalAnalysisMapper::erase(const MechanicalAnalysis &ma)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", ma.getId());

    return q.exec();
}

bool MechanicalAnalysisMapper::update(const MechanicalAnalysis &ma)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("material_id = :material_id, date = :date, mechanicalanalysis = :mechanicalanalysis").
            Where("id = :id").
            prepare();

    QByteArray serializedMAnalysis;
    QDataStream mas(&serializedMAnalysis, QIODevice::WriteOnly);

    mas << ma.measures.print();

    q.bindValue(":mechanicalanalysis", serializedMAnalysis.toPercentEncoding());
    q.bindValue(":material_id", ma.getMaterial().getId());
    q.bindValue(":date", ma.getDate());

    q.bindValue(":id", ma.getId());

    return q.exec();
}


QList <MechanicalAnalysis> MechanicalAnalysisMapper::get(QVariantHash filters)
{
    Query queryObject = Query().
                        Select(selectFields).
                        From(tableName);

    foreach(QString key, filters.keys()) {
        if (!selectFields.contains(key))
            return QList<MechanicalAnalysis>();

        queryObject.Where(key + " = :" + key);
    }

    QSqlQuery query = queryObject.prepare();

    foreach(QString key, filters.keys())
        query.bindValue(":" + key, filters.value(key));

    return makeMechanicalAnalysis(query);
}
