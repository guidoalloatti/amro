#ifndef CHEMICALMEASURE_H
#define CHEMICALMEASURE_H

#include "DataLib_global.h"

#include <QHash>
#include <QVariantHash>

/*enum ChemicalProperty {
    C,
    Mn,
    Si,
    P,
    Cr,
    Ni,
    Mo,
    Cu,
    V,
    CE
};*/
static const QList <QString> chProperties = QList <QString>() << "c"
                                                            << "mn"
                                                            << "si"
                                                            << "p"
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
