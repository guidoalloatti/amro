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
    ChemicalMeasure();
    ChemicalMeasure(QVariantHash m);

    void setMaxValue(ChemicalProperty p, double value);
    void setMinValue(ChemicalProperty p, double value);
    double getMaxValue(ChemicalProperty p);
    double getMinValue(ChemicalProperty p);
    QVariantHash print() const;

    static bool includes(ChemicalMeasure a, ChemicalMeasure target);

private:
    QHash <QString, QPair<double, double> > measures;

};

#endif // CHEMICALMEASURE_H
