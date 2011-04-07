#ifndef MECHANICALMEASURE_H
#define MECHANICALMEASURE_H

#include "DataLib_global.h"

#include <QHash>
#include <QVariantHash>

/*enum MechanicalProperty {TensionRotura,
    LimiteFluencia,
    Alargamiento,
    Estriccion,
    Resiliencia
};*/

static const QList <QString> mProperties = QList <QString>() << "tension_rotura"
                                                             << "limite_fluencia"
                                                             << "alargamiento"
                                                             << "estriccion"
                                                             << "resiliencia"
                                                             << "dureza";

typedef QString MechanicalProperty;

class DATALIBSHARED_EXPORT MechanicalMeasure
{
public:
    MechanicalMeasure() {}
    MechanicalMeasure(QVariantHash m);

    void setValue(MechanicalProperty p, double value);
    double getValue(MechanicalProperty p);
    QVariantHash print() const;

private:
    //QHash <MechanicalProperty, double> measures;
    QVariantHash measures;
};

#endif // MECHANICALMEASURE_H
