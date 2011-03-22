#ifndef MATERIALRESPONSE_H
#define MATERIALRESPONSE_H

#include "response.h"

class MaterialResponse : Response
{
    QString method;

    void newMaterial(JSONP &output, const QHash <QString, QString> &params);
    void deleteMaterial(JSONP &output, const QHash <QString, QString> &params);
    void updateMaterial(JSONP &output, const QHash <QString, QString> &params);
    void getMaterial(JSONP &output, const QHash <QString, QString> &params);

public:
    MaterialResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // MATERIALRESPONSE_H
