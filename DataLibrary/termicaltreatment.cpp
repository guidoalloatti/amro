#include "termicaltreatment.h"

TermicalTreatment::TermicalTreatment()
{
    this->id = 0;
}


void TermicalTreatment::setId(quint32 id)
{
    this->id = id;
}

void TermicalTreatment::setDate(QDate date)
{
    this->date = date;
}

void TermicalTreatment::setImagePath(QString path)
{
    this->imagePath = path;
}

void TermicalTreatment::setObservations(QString observations)
{
    this->observations = observations;
}

quint32 TermicalTreatment::getId() const
{
    return id;
}

QDate TermicalTreatment::getDate() const
{
    return date;
}

QString TermicalTreatment::getImagePath() const
{
    return imagePath;
}

QString TermicalTreatment::getObservations() const
{
    return observations;
}
