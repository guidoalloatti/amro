#ifndef CERTIFICATEMAPPER_H
#define CERTIFICATEMAPPER_H

#include "certificate.h"
#include "query.h"

class DATALIBSHARED_EXPORT CertificateMapper
{
    QString tableName;

    QList <Certificate> makeCertificates(QSqlQuery &q);

public:
    CertificateMapper();
    bool insert(const Certificate &c);
    bool update(const Certificate &c);
    bool erase(const Certificate &c);
    QList <Certificate> get(quint32 id);
    QList <Certificate> get();
};

#endif // CERTIFICATEMAPPER_H
