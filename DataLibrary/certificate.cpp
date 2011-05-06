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
    this->tTermicoPath = path;
}

void Certificate::setCertificatePath(QString path)
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

void Certificate::setOrdenCompra(QString orden)
{
    this->ordenCompra = orden;
}

void Certificate::setDescription(QString description)
{
    this->description = description;
}

void Certificate::setObservations(QString observations)
{
    this->observations = observations;
}

void Certificate::setApprover(User approver)
{
    this->approver = approver;
}

void Certificate::setReviewer(User reviewer)
{
    this->reviewer = reviewer;
}

void Certificate::setPerformer(User performer)
{
    this->performer = performer;
}

void Certificate::setState(Status s)
{
    this->state = s;
}

void Certificate::setMaterial(Material m)
{
    this->material = m;
}

void Certificate::setClient(Client c)
{
    this->client = c;
}

void Certificate::setDate(QDate d)
{
    this->date = d;
}

void Certificate::setProtN(QString protN)
{
    this->protN = protN;
}

void Certificate::setNumProbeta(QString numProbeta)
{
    this->numProbeta = numProbeta;
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

User Certificate::getPerformer() const
{
    return this->performer;
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

bool Certificate::generateCertificate(QString &err)
{
    return true;
}

QString Certificate::getCertificatePath() const
{
    return this->certificatePath;
}

QString Certificate::getTermicoPath() const
{
    return this->tTermicoPath;
}

void Certificate::setChemicalMaxValue(QString p, double max)
{
    this->chemicalAnalysis.setMaxValue(p, max);
}

void Certificate::setChemicalMinValue(QString p, double min)
{
    this->chemicalAnalysis.setMaxValue(p, min);
}

void Certificate::setMechanicalMaxValue(QString p, double value)
{
    this->mechanicalAnalysis.setMaxValue(p, value);
}

void Certificate::setMechanicalMinValue(QString p, double value)
{
    this->mechanicalAnalysis.setMinValue(p, value);
}
