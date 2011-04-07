#ifndef CHEMICALMEASURE_H
#define CHEMICALMEASURE_H

#include "DataLib_global.h"

#include <QHash>
#include <QVariantHash>
#include <QStringList>

static const QStringList chProperties = QStringList() << "c"
                                                      << "mn"
                                                      << "si"
                                                      << "p"
                                                      << "s"
                                                      << "cr"
                                                      << "ni"
                                                      << "mo"
                                                      << "cu"
                                                      << "v"
                                                      << "ce";

typedef QString ChemicalProperty;

class DATALIBSHARED_EXPORT ChemicalMeasure
{
public:
    ChemicalMeasure() {}
    ChemicalMeasure(QVariantHash m);

    void setValue(ChemicalProperty p, double value);
    double getValue(ChemicalProperty p);
    QVariantHash print() const;

private:
    //QHash <ChemicalProperty, double> measures;
    QVariantHash measures;

};

#endif // CHEMICALMEASURE_H
