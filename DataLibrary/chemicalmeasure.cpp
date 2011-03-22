#include "chemicalmeasure.h"

ChemicalMeasure::ChemicalMeasure(QVariantHash m)
{
    foreach(QString key, m.keys())
        /*switch(key) {
            case(C):
            case(Mn):
            case(Si):
            case(P):
            case(Cr):
            case(Ni):
            case(Mo):
            case(Cu):
            case(V):
            case(CE):
                this->measures[key] = m[key];
                break;
            default:
                break;
        }*/
        if (chProperties.contains(key))
            if (m[key].canConvert(QVariant::Double))
                this->measures[key] = m[key];
}

void ChemicalMeasure::setValue(ChemicalProperty p, double value)
{
    /*QString property = getString(p);

    if (property.isEmpty())
        return;*/
    if (!chProperties.contains(p))
        return;

    this->measures[p] = QVariant(value);
}

double ChemicalMeasure::getValue(ChemicalProperty p)
{
    /*QString property = getString(p);

    if (property.isEmpty())
        return;*/

    if (!this->measures.contains(p))
        return this->measures[p].toDouble();

    return -1;
}

QVariantHash ChemicalMeasure::print() const
{
    //return QVariantHash(measures);
    return this->measures;
}
