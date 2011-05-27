#ifndef TERMICALTREATMENT_H
#define TERMICALTREATMENT_H

#include "DataLib_global.h"

#include <QDate>
#include <QImage>

class DATALIBSHARED_EXPORT TermicalTreatment
{
public:
    TermicalTreatment();

    void setId(quint32 id);
    void setDate(QDate date);
    void setImagePath(QString path);
    void setObservations(QString observations);

    quint32 getId() const;
    QDate getDate() const;
    QString getImagePath() const;
    QString getObservations() const;

private:
    quint32 id;
    QDate date;
    QString imagePath;
    QString observations;

    friend class TermicalTreatmentMapper;
};

#endif // TERMICALTREATMENT_H
