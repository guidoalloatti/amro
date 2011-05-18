#ifndef RESPONSEMAPPER_H
#define RESPONSEMAPPER_H

#include <QString>
#include <QTextStream>
#include <QHash>

class ResponseMapper
{
public:
    void execute(const QString &method, QTextStream &output, const QHash <QString, QString> &params);
};

#endif // RESPONSEMAPPER_H
