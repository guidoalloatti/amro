#include "certificatemapper.h"
#include "clientmapper.h"
#include "materialmapper.h"
#include "usermapper.h"
#include "termicaltreatmentmapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("id, protn, numprobeta, client_id, material_id, approver_id, reviewer_id, performer_id, chemicalanalysis, "
                                  "mechanicalanalysis, ordencompra, description, observations, date, ttreatment_id, certificatepath, state");

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
            else {
                Client cl;
                cl.setId(0);
                c.client = cl;
            }

            QList <Material> materials = MaterialMapper().get(q.value(4).toUInt());
            if (materials.length() == 1)
                c.material = materials.first();
            else {
                Material m;
                m.setId(0);
                c.material = m;
            }

            QList <User> approvers = UserMapper().get(q.value(5).toUInt());
            if (approvers.length() == 1)
                c.approver = approvers.first();
            else {
                User u(0, "", "");
                c.approver = u;
            }

            QList <User> reviewers = UserMapper().get(q.value(6).toUInt());
            if (reviewers.length() == 1)
                c.reviewer = reviewers.first();
            else {
                User u(0, "", "");
                c.reviewer = u;
            }

            QList <User> performers = UserMapper().get(q.value(7).toUInt());
            if (performers.length() == 1)
                c.performer = performers.first();
            else {
                User u(0, "", "");
                c.performer = u;
            }

            QDataStream cds(QByteArray().fromPercentEncoding(q.value(8).toByteArray()));
            QVariantHash chemicalData;
            cds >> chemicalData;

            QDataStream mds(QByteArray().fromPercentEncoding(q.value(9).toByteArray()));
            QVariantHash mechanicalData;
            mds >> mechanicalData;

            ChemicalMeasure cMeasure(chemicalData);
            MechanicalMeasure mMeasure(mechanicalData);

            c.chemicalAnalysis = cMeasure;
            c.mechanicalAnalysis = mMeasure;

            c.ordenCompra = q.value(10).toString();
            c.description = q.value(11).toString();
            c.observations = q.value(12).toString();
            c.date = q.value(13).toDate();

            //c.tTermicoPath = q.value(14).toString();
            QList <TermicalTreatment> tts = TermicalTreatmentMapper().get(q.value(14).toUInt());
            if (tts.length() == 1)
                c.tTreatment = tts.first();
            else {
                TermicalTreatment tt;
                tt.setId(0);
                c.tTreatment = tt;
            }

            c.certificatePath = q.value(15).toString();
            c.state = Status(q.value(16).toUInt());

            cs << c;
        }

        return cs;
}

bool CertificateMapper::insert(const Certificate &c)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :protn, :numprobeta, :client_id, :material_id, :approver_id, :reviewer_id, :performer_id, :chemicalanalysis, "
                   ":mechanicalanalysis, :ordencompra, :description, :observations, :date, :ttreatment_id, :certificatepath, :state").
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
    q.bindValue("performer_id", c.getPerformer().getId());
    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":mechanicalanalysis", serializedMAnalysis.toPercentEncoding());
    q.bindValue(":ordencompra", c.getOrdenCompra());
    q.bindValue(":description", c.getDescription());
    q.bindValue(":observations", c.getObservations());
    q.bindValue(":date", c.getDate().toString(Qt::ISODate));
    //q.bindValue(":termicopath", c.getTermicoPath());
    q.bindValue(":ttreatment_id", c.getTermicalTreatment().getId());
    q.bindValue("certificatepath", c.getCertificatePath());
    q.bindValue(":state", c.getState());

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
            Set("DEFAULT, :protn, :numprobeta, :client_id, :material_id, :approver_id, :reviewer_id, :performer_id, :chemicalanalysis, "
                ":mechanicalanalysis, :ordencompra, :description, :observations, :date, :ttreatment_id, :certificatepath, :state").
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
    q.bindValue(":performer_id", c.getPerformer().getId());
    q.bindValue(":chemicalanalysis", serializedCAnalysis.toPercentEncoding());
    q.bindValue(":mechanicalanalysis", serializedMAnalysis.toPercentEncoding());
    q.bindValue(":ordencompra", c.getOrdenCompra());
    q.bindValue(":description", c.getDescription());
    q.bindValue(":observations", c.getObservations());
    q.bindValue(":date", c.getDate().toString(Qt::ISODate));
    //q.bindValue(":termicopath", c.getTermicoPath());
    q.bindValue("ttreatment_id", c.getTermicalTreatment().getId());
    q.bindValue("certificatepath", c.getCertificatePath());
    q.bindValue("state", c.getState());

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

QList <Certificate> CertificateMapper::get()
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      prepare();

    return makeCertificates(query);
}

quint32 CertificateMapper::getNextId()
{
    QSqlQuery q =
            Query().Select("id").
            From(tableName).
            OrderBy("id", false).
            prepare();


    bool s = q.exec();
    if (!s)
        return 0;

    q.next();
    return q.value(0).toUInt() + 1;
}

QList <Certificate> CertificateMapper::get(QVariantHash filters, QString order)
{
    Query queryObject = Query().
                        Select(selectFields).
                        From(tableName);

    qDebug() << filters;

    if (!selectFields.contains(order))
        return QList<Certificate>();

    foreach(QString key, filters.keys()) {
        if (!selectFields.contains(key))
            return QList<Certificate>();

        queryObject.Where(key + " = :" + key);
    }

    queryObject.OrderBy(order, false);

    QSqlQuery query = queryObject.prepare();

    foreach(QString key, filters.keys())
        query.bindValue(":" + key, filters.value(key));

    return makeCertificates(query);
}

