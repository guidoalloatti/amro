#include "jsonp.h"

#include <QtCore>

JSONP::JSONP(QTextStream *output, QString callback)
{
    *output << callback << "({";
    output->flush();

    this->output = output;
}

void JSONP::serializeKey(const QString &key)
{
    *output << sep << "\"" << key << "\": ";
}

void JSONP::serializeKey(const QVariant &key)
{
    serializeKey(key.toString());
}

void JSONP::serializeValue(const QVariant &value)
{
    if (value.type() == QVariant::Bool)
    {
        if (value.toBool())
            *output << "true";
        else
            *output << "false";
    }
    else if (value.type() == QVariant::String)
        // HACER: probablemente deba escapar las comillas dentro de la string
        *output << "\"" << value.toString() << "\"";
    else if (value.type() == QVariant::List)
    {
        *output << "[";

        QString s;

        foreach (QVariant e, value.toList())
        {
            *output << s;
            serializeValue(e);
            s = ", ";
        }

        *output << "]";
    }
    else if (value.type() == QVariant::Hash)
    {
        // HACER: esto deberia crear un nuevo objeto JSON que se encarga solo
        *output << "{";

        QString s;

        sep = ""; // HACER: arreglar este HACK

        foreach (QString k, value.toHash().keys())
        {
            *output << s;
            serializeKey(k);
            serializeValue(value.toHash().value(k));
            s = ", ";
        }

        *output << "}";
    }
    else if (value.type() == QVariant::Int)
        *output << value.toString();
    else if (value.type() == QVariant::Double)
        *output << value.toString();
    else if (value.type() == QVariant::DateTime || value.type() == QVariant::Date)
        // HACER: eliminar la necesidad de este caso
        *output << "\"" << value.toString() << "\"";
    else // HACER: deberia poner algun mensaje aca
        *output << value.toString();
}

void JSONP::add(const QVariant &key, const QVariant &value)
{
    serializeKey(key);
    serializeValue(value);

    output->flush();

    sep = ", ";
}

void JSONP::close()
{
    *output << "});";
    output->flush();
}
