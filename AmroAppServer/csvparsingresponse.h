#ifndef CSVPARSINGRESPONSE_H
#define CSVPARSINGRESPONSE_H

#include "response.h"

class CSVParsingResponse: public Response
{
    QString method;

    static void parseCSV(JSONP &output, const QHash <QString, QString> &params);
    static void getOC(JSONP &output, const QHash <QString, QString> &params);

public:
    CSVParsingResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // CSVPARSINGRESPONSE_H
