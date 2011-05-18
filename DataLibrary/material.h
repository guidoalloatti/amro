#ifndef MATERIAL_H
#define MATERIAL_H

#include "DataLib_global.h"

#include <QString>

#include "chemicalmeasure.h"
#include "mechanicalmeasure.h"

class DATALIBSHARED_EXPORT Material
{
public:
    Material() {}
    Material(quint32 id, QString name, QString description);

    void setId(quint32 id);
    void setName(QString name);
    void setDescription(QString desc);

    quint32 getId() const;
    QString getName() const;
    QString getDescription() const;

    void setChemicalLimit(ChemicalMeasure measure);
    ChemicalMeasure getChemicalLimit() const;
    void setChemicalMaxValue(QString p, double value);
    void setChemicalMinValue(QString p, double value);

    void setMechanicalLimit(MechanicalMeasure measure);
    MechanicalMeasure getMechanicalLimit() const;
    void setMechanicalMaxValue(QString p, double value);
    void setMechanicalMinValue(QString p, double value);

private:
    quint32 id;
    QString name, description;

    ChemicalMeasure chemicalLimits;
    MechanicalMeasure mechanicalLimits;

    friend class MaterialMapper;
};

#endif // MATERIAL_H
