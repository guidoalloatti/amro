#ifndef CERTIFICATERESPONSE_H
#define CERTIFICATERESPONSE_H

#include "response.h"

class CertificateResponse : Response
{
    QString method;

    void newCertificate(JSONP &output, const QHash <QString, QString> &params);
    void deleteCertificate(JSONP &output, const QHash <QString, QString> &params);
    void updateCertificate(JSONP &output, const QHash <QString, QString> &params);
    void getCertificate(JSONP &output, const QHash <QString, QString> &params);

public:
    CertificateResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // CERTIFICATERESPONSE_H
