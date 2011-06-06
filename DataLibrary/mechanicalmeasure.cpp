#include "mechanicalmeasure.h"

#include <QDebug>
#include <QStringList>


MechanicalMeasure::MechanicalMeasure()
{
    foreach(QString property, mProperties)
        this->measures[property] = QPair <double, double> (0, 0);
}

MechanicalMeasure::MechanicalMeasure(QVariantHash m)
{
    foreach(QString property, mProperties) {
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

void MechanicalMeasure::setMaxValue(MechanicalProperty p, double max)
{
    if (!mProperties.contains(p))
        return;

    this->measures[p].first = max;
}

void MechanicalMeasure::setMinValue(MechanicalProperty p, double min)
{
    if (!mProperties.contains(p))
        return;

    this->measures[p].second = min;
}

double MechanicalMeasure::getMaxValue(MechanicalProperty p)
{
    QStringList properties = this->measures.keys();
    if (properties.contains(p))
        return this->measures[p].first;

    return -1;
}

double MechanicalMeasure::getMinValue(MechanicalProperty p)
{
    QStringList properties = this->measures.keys();
    if (properties.contains(p))
        return this->measures[p].second;

    return -1;
}

QVariantHash MechanicalMeasure::print() const
{
    QVariantHash m;

    foreach(QString key, this->measures.keys())
        m[key] = QVariantList() << QVariant(measures[key].first)
                                << QVariant(measures[key].second);

    return m;
}

bool MechanicalMeasure::includes(MechanicalMeasure a, MechanicalMeasure target)
{
    foreach(QString key, a.measures.keys())
        if (target.measures[key].second > a.measures[key].first ||
            target.measures[key].first < a.measures[key].first)
            return false;

    return true;
}
