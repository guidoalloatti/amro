#include "certificatemapper.h"
#include "clientmapper.h"
#include "materialmapper.h"
#include "usermapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("id, protn, numprobeta, client_id, material_id, approver_id, reviewer_id, chemicalanalysis, "
                                  "mechanicalanalysis, ordencompra, description, observations, date, termicopath");

CertificateMapper::CertificateMapper()
{
    this->tableName = "certificates";
}

QList <Certificate> CertificateMapper::makeCertificates(QSqlQuery &q)
{
        QList <Certificate> cs;

        q.exec();

        while (q.next())
        {
            Certificate c;

            c.id = q.value(0).toUInt();
            c.protN = q.value(1).toString();
            c.numProbeta = q.value(2).toString();

            QList <Client> clients = ClientMapper().get(q.value(3).toUInt());
            if (clients.length() == 1)
                c.client = clients.first();
            else
                continue;

            QList <Material> materials = MaterialMapper().get(q.value(4).toUInt());
            if (materials.length() == 1)
                c.material = materials.first();
            else
                continue;

            QList <User> approvers = UserMapper().get(q.value(5).toUInt());
            if (approvers.length() == 1)
                c.approver = approvers.first();
            else
                continue;

            QList <User> reviewers = UserMapper().get(q.value(6).toUInt());
            if (reviewers.length() == 1)
                c.reviewer = reviewers.first();
            else
                continue;

            QDataStream cds(QByteArray().fromPercentEncoding(q.value(7).toByteArray()));
            QVariantHash chemicalData;
            cds >> chemicalData;

            QDataStream mds(QByteArray().fromPercentEncoding(q.value(8).toByteArray()));
            QVariantHash mechanicalData;
            mds >> mechanicalData;

            ChemicalMeasure cMeasure(chemicalData);
            MechanicalMeasure mMeasure(mechanicalData);

            c.chemicalAnalysis = cMeasure;
            c.mechanicalAnalysis = mMeasure;

            c.ordenCompra = q.value(9).toString();
            c.description = q.value(10).toString();
            c.observations = q.value(11).toString();
            c.date = q.value(12).toDate();
            c.tTermicoPath = q.value(13).toString();

            cs << c;
        }

        return cs;
}

bool CertificateMapper::insert(const Certificate &c)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, protn, numprobeta, client_id, material_id, approver_id, reviewer_id, chemicalanalysis, "
                   "mechanicalanalysis, ordencompra, description, observations, date, termicopath").
            prepare();

    QByteArray serializedCAnalysis;
    QDataStream cas(&serializedCAnalysis, QIODevice::WriteOnly);

    cas << c.chemicalAnalysis.print();

    QByteArray serializedMAnalysis;
    QDataStream mas(&serializedMAnalysis, QIODevice::WriteOnly);

    mas << c.mechanicalAnalysis.print();

    q.bindValue(":protn", c.getProtN());
    q.bindValue(":numprobeta", c.getNumProbeta());
    q.bindValue("client_id", c.getClient().getId());
    q.bindValue(":material_id", c.getMaterial().getId());
    q.bindValue("approver_id", c.getApprover().getId());
    q.bindValue(":reviewer_id", c.getReviewer().getId());
    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":mechanicalanalysis", serializedMAnalysis.toPercentEncoding());
    q.bindValue(":ordencompra", c.getOrdenCompra());
    q.bindValue(":description", c.getDescription());
    q.bindValue(":observations", c.getObservations());
    q.bindValue(":date", c.getDate().toString(Qt::ISODate));
    q.bindValue(":termicopath", c.getTermicoPath());

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool CertificateMapper::erase(const Certificate &c)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", c.getId());

    return q.exec();
}

bool CertificateMapper::update(const Certificate &c)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("DEFAULT, protn, numprobeta, client_id, material_id, approver_id, reviewer_id, chemicalanalysis, "
                "mechanicalanalysis, ordencompra, description, observations, date, termicopath").
            Where("id = :id").
            prepare();

    QByteArray serializedCAnalysis;
    QDataStream cas(&serializedCAnalysis, QIODevice::WriteOnly);

    cas << c.chemicalAnalysis.print();

    QByteArray serializedMAnalysis;
    QDataStream mas(&serializedMAnalysis, QIODevice::WriteOnly);

    mas << c.mechanicalAnalysis.print();

    q.bindValue(":protn", c.getProtN());
    q.bindValue(":numprobeta", c.getNumProbeta());
    q.bindValue("client_id", c.getClient().getId());
    q.bindValue(":material_id", c.getMaterial().getId());
    q.bindValue("approver_id", c.getApprover().getId());
    q.bindValue(":reviewer_id", c.getReviewer().getId());
    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":mechanicalanalysis", serializedMAnalysis.toPercentEncoding());
    q.bindValue(":ordencompra", c.getOrdenCompra());
    q.bindValue(":description", c.getDescription());
    q.bindValue(":observations", c.getObservations());
    q.bindValue(":date", c.getDate().toString(Qt::ISODate));
    q.bindValue(":termicopath", c.getTermicoPath());

    q.bindValue(":id", c.getId());

    return q.exec();
}


QList <Certificate> CertificateMapper::get(quint32 id)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", id);

    return makeCertificates(query);
}

QList <Certificate> CertificateMapper::get(const QString &name)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("name = :name").
                      prepare();

    query.bindValue(":name", name);

    return makeCertificates(query);
}
