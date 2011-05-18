#ifndef CHEMICALANALYSIS_H
#define CHEMICALANALYSIS_H

#include "material.h"
#include "chemicalmeasure.h"
#include "query.h"

class DATALIBSHARED_EXPORT ChemicalAnalysis
{
public:
    ChemicalAnalysis();

    void setNumProbeta(QString numProbeta);
    void setId(quint32 id);
    void setMaterial(Material m);
    void setDate(QDate date);
    void setMeasures(ChemicalMeasure cm);
    void setTTDate(QDate date);

    QString getNumProbeta() const;
    quint32 getId() const;
    Material getMaterial() const;
    QDate getDate() const;
    ChemicalMeasure getMeasures() const;
    QDate GetTTDate() const;

private:
    quint32 id;
    QString numProbeta;
    QDate date;
    Material material;
    ChemicalMeasure measures;
    QDate TTDate;

    friend class ChemicalAnalysisMapper;
};

#endif // CHEMICALANALYSIS_H