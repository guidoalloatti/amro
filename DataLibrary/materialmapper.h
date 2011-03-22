#ifndef MATERIALMAPPER_H
#define MATERIALMAPPER_H

#include "material.h"
#include "query.h"

class DATALIBSHARED_EXPORT MaterialMapper
{
    QString tableName;

    QList <Material> makeMaterials(QSqlQuery &q);

public:
    MaterialMapper();
    bool insert(const Material &m);
    bool update(const Material &m);
    bool erase(const Material &m);
    QList <Material> get(quint32 id);
    QList <Material> get(const QString &name);

};

#endif // MATERIALMAPPER_H
