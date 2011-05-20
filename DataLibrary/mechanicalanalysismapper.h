#ifndef MECHANICALANALYSISMAPPER_H
#define MECHANICALANALYSISMAPPER_H

#include "mechanicalanalysis.h"
#include "query.h"

class DATALIBSHARED_EXPORT MechanicalAnalysisMapper
{
    QString tableName;

    QList <MechanicalAnalysis> makeMechanicalAnalysis(QSqlQuery &q);

public:
    MechanicalAnalysisMapper();
    bool insert(const MechanicalAnalysis &ma);
    bool update(const MechanicalAnalysis &ma);
    bool erase(const MechanicalAnalysis &ma);
    QList <MechanicalAnalysis> get(QVariantHash filters, QString order);
};

#endif // MECHANICALANALYSISMAPPER_H
