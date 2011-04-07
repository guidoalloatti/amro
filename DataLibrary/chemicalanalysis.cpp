#include "chemicalanalysis.h"

ChemicalAnalysis::ChemicalAnalysis()
{
}

void ChemicalAnalysis::setNumProbeta(QString numProbeta)
{
    this->numProbeta = numProbeta;
}

void ChemicalAnalysis::setId(quint32 id)
{
    this->id = id;
}

void ChemicalAnalysis::setMaterial(Material m)
{
    this->material = m;
}

void ChemicalAnalysis::setDate(QDate date)
{
    this->date = date;
}

void ChemicalAnalysis::setMeasures(ChemicalMeasure ca)
{
    this->measures = ca;
}

QString ChemicalAnalysis::getNumProbeta() const
{
    return this->numProbeta;
}

quint32 ChemicalAnalysis::getId() const
{
    return this->id;
}

Material ChemicalAnalysis::getMaterial() const
{
    return this->material;
}

QDate ChemicalAnalysis::getDate() const
{
    return this->date;
}

ChemicalMeasure ChemicalAnalysis::getMeasures() const
{
    return this->measures;
}


