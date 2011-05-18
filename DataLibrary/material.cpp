#include "material.h"

Material::Material(quint32 id, QString name, QString description)
{
    this->id = id;
    this->name = name;
    this->description = description;
}

void Material::setId(quint32 id)
{
    this->id = id;
}

void Material::setName(QString name)
{
    this->name = name;
}

void Material::setDescription(QString desc)
{
    this->description = desc;
}

quint32 Material::getId() const
{
    return this->id;
}

QString Material::getName() const
{
    return this->name;
}

QString Material::getDescription() const
{
    return this->description;
}

void Material::setChemicalLimit(ChemicalMeasure measure)
{
    this->chemicalLimits = measure;
}

ChemicalMeasure Material::getChemicalLimit() const
{
    return this->chemicalLimits;
}

void Material::setChemicalMaxValue(QString p, double max)
{
    this->chemicalLimits.setMaxValue(p, max);
}

void Material::setChemicalMinValue(QString p, double min)
{
    this->chemicalLimits.setMinValue(p, min);
}

void Material::setMechanicalLimit(MechanicalMeasure measure)
{
    this->mechanicalLimits = measure;
}

MechanicalMeasure Material::getMechanicalLimit() const
{
    return this->mechanicalLimits;
}

void Material::setMechanicalMaxValue(QString p, double value)
{
    this->mechanicalLimits.setMaxValue(p, value);
}

void Material::setMechanicalMinValue(QString p, double value)
{
    this->mechanicalLimits.setMinValue(p, value);
}
