#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include "DataLib_global.h"
#include "client.h"
#include "user.h"
#include "chemicalmeasure.h"
#include "mechanicalmeasure.h"
#include "material.h"

#include <QString>
#include <QList>
#include <QDate>
#include <QObject>



enum Status {PASSED, FAILED};

class DATALIBSHARED_EXPORT Certificate
{
public:
    Certificate() {}
    Certificate(quint32 id, QString protN, QString numProbeta);

    void setId(quint32 id);
    void setImagePath(QString path);
    void setCertificatePath(QString path);
    void setChemicalAnalysis(ChemicalMeasure ca);
    void setMechanicalAnalysis(MechanicalMeasure ma);
    void setOrdenCompra(QString orden);
    void setDescription(QString description);
    void setObservations(QString observations);
    void setApprover(User approver);
    void setReviewer(User reviewer);
    void setPerformer(User performer);
    void setState(Status s);
    void setMaterial(Material m);
    void setClient(Client c);
    void setDate(QDate d);
    void setProtN(QString protN);
    void setNumProbeta(QString numProbeta);
    void setChemicalMaxValue(QString p, double value);
    void setChemicalMinValue(QString p, double value);

    void setMechanicalMaxValue(QString p, double value);
    void setMechanicalMinValue(QString p, double value);

    quint32 getId() const;
    QString getProtN() const;
    QString getNumProbeta() const;
    Client getClient() const;
    QDate getDate() const;
    Status getState() const;
    User getApprover() const;
    User getReviewer() const;
    User getPerformer() const;
    ChemicalMeasure getChemicalAnalysis() const;
    MechanicalMeasure getMechanicalAnalysis() const;
    Material getMaterial() const;
    QString getOrdenCompra() const;
    QString getDescription() const;
    QString getObservations() const;

    bool generateCertificate(QString &err);
    QString getCertificatePath() const;
    QString getTermicoPath() const;

private:
    quint32 id;
    QString protN, numProbeta;
    Client client;
    User approver, reviewer, performer;
    ChemicalMeasure chemicalAnalysis;
    MechanicalMeasure mechanicalAnalysis;
    Material material;
    QString ordenCompra, description, observations;
    QDate date;
    QString tTermicoPath, certificatePath;
    Status state;

    friend class CertificateMapper;
};

Q_DECLARE_METATYPE(Certificate);

#endif // CERTIFICATE_H
