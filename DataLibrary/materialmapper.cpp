#include "materialmapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("id, name, description, chemicalanalysis, mechanicalanalysis");

MaterialMapper::MaterialMapper()
{
    this->tableName = "materials";
}

QList <Material> MaterialMapper::makeMaterials(QSqlQuery &q)
{
        QList <Material> ms;

        q.exec();

        while (q.next())
        {
            Material m;

            QDataStream cds(QByteArray().fromPercentEncoding(q.value(3).toByteArray()));
            QVariantHash chemicalData;
            cds >> chemicalData;

            QDataStream mds(QByteArray().fromPercentEncoding(q.value(4).toByteArray()));
            QVariantHash mechanicalData;
            mds >> mechanicalData;

            ChemicalMeasure cMeasure(chemicalData);
            MechanicalMeasure mMeasure(mechanicalData);

            m.id = q.value(0).toUInt();
            m.name = q.value(1).toString();
            m.description = q.value(2).toString();
            m.setChemicalLimit(cMeasure);
            m.setMechanicalLimit(mMeasure);

            ms << m;
        }

        return ms;
}

bool MaterialMapper::insert(const Material &m)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :name, :description, :chemicalanalysis, :mechanicalanalysis").
            prepare();

    QByteArray serializedCAnalysis;
    QDataStream cas(&serializedCAnalysis, QIODevice::WriteOnly);

    cas << m.getChemicalLimit().print();

    QByteArray serializedMAnalysis;
    QDataStream mas(&serializedMAnalysis, QIODevice::WriteOnly);

    mas << m.getMechanicalLimit().print();

    q.bindValue(":name", m.getName());
    q.bindValue(":description", m.getDescription());
    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":mechanicalanalysis", serializedMAnalysis.toPercentEncoding());

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool MaterialMapper::erase(const Material &m)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", m.getId());

    return q.exec();
}

bool MaterialMapper::update(const Material &m)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("DEFAULT, :name, :description, :chemicalanalysis, :mechanicalanalysis").
            Where("id = :id").
            prepare();

    QByteArray serializedCAnalysis;
    QDataStream cas(&serializedCAnalysis, QIODevice::WriteOnly);

    cas << m.getChemicalLimit().print();

    QByteArray serializedMAnalysis;
    QDataStream mas(&serializedMAnalysis, QIODevice::WriteOnly);

    mas << m.getMechanicalLimit().print();

    q.bindValue(":name", m.getName());
    q.bindValue(":description", m.getDescription());
    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":mechanicalanalysis", serializedMAnalysis.toPercentEncoding());

    q.bindValue(":id", m.id);

    return q.exec();
}


QList <Material> MaterialMapper::get(quint32 id)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", id);

    return makeMaterials(query);
}

QList <Material> MaterialMapper::get(const QString &name)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("name = :name").
                      prepare();

    query.bindValue(":name", name);

    return makeMaterials(query);
}

