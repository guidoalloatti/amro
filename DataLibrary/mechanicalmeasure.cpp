#include "mechanicalmeasure.h"

/*QString getString(MechanicalProperty p)
{
    switch(p) {
        case(TensionRotura):
            return "tension_rotura";
        case(LimiteFluencia):
            return "limite_fluencia";
        case(Estriccion):
            return "estriccion";
        case(Resiliencia):
            return "resiliencia";
        default:
            return QString("");
    }
}*/

MechanicalMeasure::MechanicalMeasure(QVariantHash m)
{
    foreach(QString key, m.keys())
        /*switch(value) {
            case(TensionRotura):
            case(LimiteFluencia):
            case(Estriccion):
            case(Resiliencia):
                this->measures[key] = m[key];
                break;
            default:
                break;
        }*/
        if (mProperties.contains(key))
            if (m[key].canConvert(QVariant::Double))
                this->measures[key] = m[key];
}

void MechanicalMeasure::setValue(MechanicalProperty p, double value)
{
    /*QString property = getString(p);

    if (property.isEmpty())
        return;*/
    if (!mProperties.contains(p))
        return;

    this->measures[p] = QVariant(value);
}

double MechanicalMeasure::getValue(MechanicalProperty p)
{
    /*QString property = getString(p);

    if (property.isEmpty())
        return;*/

    if (this->measures.contains(p))
        return this->measures[p].toDouble();

    return -1;
}

QVariantHash MechanicalMeasure::print() const
{
    //return QVariantHash(measures);
    return this->measures;
}
