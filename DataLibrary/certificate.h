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

enum Status {PASSED, FAILED};

class DATALIBSHARED_EXPORT Certificate
{
public:
    Certificate() {}
    Certificate(quint32 id, QString protN, QString numProbeta);

    void setId(quint32 id);
    void setImagePath(QString path);
    void setChemicalAnalysis(ChemicalMeasure ca);
    void setMechanicalAnalysis(MechanicalMeasure ma);

    quint32 getId() const;
    QString getProtN() const;
    QString getNumProbeta() const;
    Client getClient() const;
    QDate getDate() const;
    Status getState() const;
    User getApprover() const;
    User getReviewer() const;
    ChemicalMeasure getChemicalAnalysis() const;
    MechanicalMeasure getMechanicalAnalysis() const;
    Material getMaterial() const;
    QString getOrdenCompra() const;
    QString getDescription() const;
    QString getObservations() const;

    int generateCertificate();
    QString getCertificatePath() const;
    QString getTermicoPath() const;

private:
    quint32 id;
    QString protN, numProbeta;
    Client client;
    User approver, reviewer;
    ChemicalMeasure chemicalAnalysis;
    MechanicalMeasure mechanicalAnalysis;
    Material material;
    QString ordenCompra, description, observations;
    QDate date;
    QString tTermicoPath, certificatePath;
    Status state;

    friend class CertificateMapper;
};

#endif // CERTIFICATE_H
