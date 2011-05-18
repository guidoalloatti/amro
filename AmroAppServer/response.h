#ifndef RESPONSE_H
#define RESPONSE_H

#include <QTextStream>
#include <QHash>
#include <QString>

#include "jsonp.h"

class Response
{
protected:
    QHash <QString, void (*) (JSONP &, const QHash <QString, QString> &)> methodTable;

public:
    Response();
    virtual void generate(QString method, JSONP &output, const QHash <QString, QString> &params) = 0;
};

#endif // RESPONSE_H
