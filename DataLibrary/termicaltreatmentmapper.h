#ifndef TERMICALTREATMENTMAPPER_H
#define TERMICALTREATMENTMAPPER_H

#include "termicaltreatment.h"
#include "query.h"

class DATALIBSHARED_EXPORT TermicalTreatmentMapper
{
    QString tableName;

    QList <TermicalTreatment> makeTTreatments(QSqlQuery &q);

public:
    TermicalTreatmentMapper();

    bool insert(const TermicalTreatment &tt);
    bool update(const TermicalTreatment &tt);
    bool erase(const TermicalTreatment &tt);
    QList <TermicalTreatment> get();
    QList <TermicalTreatment> get(quint32 id);
    QList <TermicalTreatment> get(const QDate date);
};

#endif // TERMICALTREATMENTMAPPER_H
