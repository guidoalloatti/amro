#ifndef MATERIALRESPONSE_H
#define MATERIALRESPONSE_H

#include "response.h"

class MaterialResponse : public Response
{
    QString method;

    static void newMaterial(JSONP &output, const QHash <QString, QString> &params);
    static void deleteMaterial(JSONP &output, const QHash <QString, QString> &params);
    static void updateMaterial(JSONP &output, const QHash <QString, QString> &params);
    static void getMaterial(JSONP &output, const QHash <QString, QString> &params);

public:
    MaterialResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // MATERIALRESPONSE_H

