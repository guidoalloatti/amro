#ifndef JSONP_H
#define JSONP_H

#include <QTextStream>
#include <QVariant>

// HACER: poner un destructor que lo cierre automaticamente y sea seguro (no cierre dos veces)

class JSONP
{
    QTextStream *output;
    QString sep;

    void serializeKey(const QString &key);
    void serializeKey(const QVariant &key);
    void serializeValue(const QVariant &value);

public:
    JSONP(QTextStream *output, QString callback);
    void add(const QVariant &key, const QVariant &value);
    void close();
};

#endif // JSONP_H
