#include "mechanicalanalysis.h"

MechanicalAnalysis::MechanicalAnalysis()
{
}

void MechanicalAnalysis::setId(quint32 id)
{
    this->id = id;
}

void MechanicalAnalysis::setMaterial(Material m)
{
    this->material = m;
}

void MechanicalAnalysis::setDate(QDate date)
{
    this->date = date;
}

void MechanicalAnalysis::setMeasures(MechanicalMeasure ma)
{
    this->measures = ma;
}

quint32 MechanicalAnalysis::getId() const
{
    return this->id;
}

Material MechanicalAnalysis::getMaterial() const
{
    return this->material;
}

QDate MechanicalAnalysis::getDate() const
{
    return this->date;
}

MechanicalMeasure MechanicalAnalysis::getMeasures() const
{
    return this->measures;
}

void MechanicalAnalysis::setMeasureMaxValue(QString p, double value)
{
    this->measures.setMaxValue(p, value);
}

void MechanicalAnalysis::setMeasureMinValue(QString p, double value)
{
    this->measures.setMinValue(p, value);
}




