#include "chemicalmeasure.h"

#include <QDebug>

ChemicalMeasure::ChemicalMeasure()
{
    foreach(QString property, chProperties)
        this->measures[property] = QPair <double, double> (0, 0);
}

ChemicalMeasure::ChemicalMeasure(QVariantHash m)
{
    foreach(QString property, chProperties) {
        this->measures[property] = QPair <double, double> (0, 0);

        if (m.keys().contains(property)) {
            if (m.value(property).canConvert(QVariant::List)) {
                QVariantList list = m[property].toList();

                if (list.length() > 2 || list.empty())
                    continue;

                int index = 0;
                foreach(QVariant value, list) {
                    if (value.canConvert(QVariant::Double)) {
                        if (!index)
                            this->measures[property].first = value.toDouble();
                        else
                            this->measures[property].second = value.toDouble();
                    }
                    index++;
                }

            }
        }
    }

}

void ChemicalMeasure::setMaxValue(ChemicalProperty p, double max)
{
    if (!chProperties.contains(p))
        return;

    this->measures[p].first = max;
}

void ChemicalMeasure::setMinValue(ChemicalProperty p, double min)
{
    if (!chProperties.contains(p))
        return;
    this->measures[p].second = min;

}

double ChemicalMeasure::getMaxValue(ChemicalProperty p)
{
    QStringList properties = this->measures.keys();
    if (properties.contains(p))
        return this->measures[p].first;

    return -1;
}

double ChemicalMeasure::getMinValue(ChemicalProperty p)
{
    QStringList properties = this->measures.keys();
    if (properties.contains(p))
        return this->measures[p].second;

    return -1;
}

QVariantHash ChemicalMeasure::print() const
{
    QVariantHash m;

    foreach(QString key, this->measures.keys())
        m[key] = QVariantList() << QVariant(measures[key].first)
                                << QVariant(measures[key].second);

    return m;
}

bool ChemicalMeasure::includes(ChemicalMeasure a, ChemicalMeasure target)
{
    foreach(QString key, a.measures.keys())
        if (target.measures[key].second > a.measures[key].first ||
            target.measures[key].first < a.measures[key].first)
            return false;

    return true;
}
