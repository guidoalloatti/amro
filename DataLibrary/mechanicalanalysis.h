#ifndef MECHANICALANALYSIS_H
#define MECHANICALANALYSIS_H

#include "material.h"
#include "mechanicalmeasure.h"
#include "query.h"

class DATALIBSHARED_EXPORT MechanicalAnalysis
{
public:
    MechanicalAnalysis();

    void setId(quint32 id);
    void setMaterial(Material m);
    void setDate(QDate date);
    void setMeasures(MechanicalMeasure ma);

    quint32 getId() const;
    Material getMaterial() const;
    QDate getDate() const;
    MechanicalMeasure getMeasures() const;
    void setMeasureMaxValue(QString p, double value);
    void setMeasureMinValue(QString p, double value);

private:
    quint32 id;
    QDate date;
    Material material;
    MechanicalMeasure measures;

    friend class MechanicalAnalysisMapper;
};

#endif // MECHANICALANALYSIS_H
