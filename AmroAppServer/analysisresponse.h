#ifndef ANALYSISRESPONSE_H
#define ANALYSISRESPONSE_H

#include "response.h"

class AnalysisResponse: public Response
{
    QString method;

    static void parseCA(JSONP &output, const QHash <QString, QString> &params);
    static void deleteCA(JSONP &output, const QHash <QString, QString> &params);
    static void checkCA(JSONP &output, const QHash <QString, QString> &params);

    static void loadMA(JSONP &output, const QHash <QString, QString> &params);
    static void deleteMA(JSONP &output, const QHash <QString, QString> &params);
    static void getMA(JSONP &output, const QHash <QString, QString> &params);

public:
    AnalysisResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // ANALYSISRESPONSE_H
