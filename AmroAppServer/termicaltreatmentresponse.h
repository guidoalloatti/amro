#ifndef TERMICALTREATMENTRESPONSE_H
#define TERMICALTREATMENTRESPONSE_H

#include "response.h"

class TermicalTreatmentResponse : public Response
{
    QString method;

    static void newTTreatment(JSONP &output, const QHash <QString, QString> &params);
    static void deleteTTreatment(JSONP &output, const QHash <QString, QString> &params);
    static void updateTTreatment(JSONP &output, const QHash <QString, QString> &params);
    static void getTTreatment(JSONP &output, const QHash <QString, QString> &params);


public:
    TermicalTreatmentResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // TERMICALTREATMENTRESPONSE_H
