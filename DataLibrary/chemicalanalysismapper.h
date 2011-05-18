#ifndef CHEMICALANALYSISMAPPER_H
#define CHEMICALANALYSISMAPPER_H

#include "chemicalanalysis.h"
#include "query.h"

class DATALIBSHARED_EXPORT ChemicalAnalysisMapper
{
    QString tableName;

    QList <ChemicalAnalysis> makeChemicalAnalysis(QSqlQuery &q);

public:
    ChemicalAnalysisMapper();
    bool insert(const ChemicalAnalysis &ca);
    bool update(const ChemicalAnalysis &ca);
    bool erase(const ChemicalAnalysis &ca);
    QList <ChemicalAnalysis> get(QVariantHash filters);
};

#endif // CHEMICALANALYSISMAPPER_H
