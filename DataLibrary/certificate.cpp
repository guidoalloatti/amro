#include "certificate.h"

Certificate::Certificate(quint32 id, QString protN, QString numProbeta)
{
    this->id = id;
    this->protN = protN;
    this->numProbeta = numProbeta;
}

void Certificate::setId(quint32 id)
{
    this->id = id;
}

void Certificate::setImagePath(QString path)
{
    this->certificatePath = path;
}

void Certificate::setChemicalAnalysis(ChemicalMeasure ca)
{
    this->chemicalAnalysis = ca;
}

void Certificate::setMechanicalAnalysis(MechanicalMeasure ma)
{
    this->mechanicalAnalysis = ma;
}

quint32 Certificate::getId() const
{
    return this->id;
}

QString Certificate::getProtN() const
{
    return this->protN;
}

QString Certificate::getNumProbeta() const
{
    return this->numProbeta;
}

Client Certificate::getClient() const
{
    return this->client;
}

QDate Certificate::getDate() const
{
    return this->date;
}

Status Certificate::getState() const
{
    return this->state;
}

User Certificate::getApprover() const
{
    return this->approver;
}

User Certificate::getReviewer() const
{
    return this->reviewer;
}

ChemicalMeasure Certificate::getChemicalAnalysis() const
{
    return this->chemicalAnalysis;
}

MechanicalMeasure Certificate::getMechanicalAnalysis() const
{
    return this->mechanicalAnalysis;
}

Material Certificate::getMaterial() const
{
    return this->material;
}

QString Certificate::getOrdenCompra() const
{
    return this->ordenCompra;
}

QString Certificate::getDescription() const
{
    return this->description;
}

QString Certificate::getObservations() const
{
    return this->observations;
}

int Certificate::generateCertificate()
{
    //GENERAR CERTIFICADO EN HTML, IMPRIMIENDOLO EN PDF.
    //DESPUES VER CÓMO MODULARIZAR MAS ESTE PROCEDIMIENTO.
    //CANDIDATO... CertificateGenerator.
}

QString Certificate::getCertificatePath() const
{
    return this->certificatePath;
}

QString Certificate::getTermicoPath() const
{
    return this->tTermicoPath;
}

