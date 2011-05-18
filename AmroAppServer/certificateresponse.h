#ifndef CERTIFICATERESPONSE_H
#define CERTIFICATERESPONSE_H

#include "response.h"

class CertificateResponse : public Response
{
    QString method;

    static void newCertificate(JSONP &output, const QHash <QString, QString> &params);
    static void deleteCertificate(JSONP &output, const QHash <QString, QString> &params);
    //static void updateCertificate(JSONP &output, const QHash <QString, QString> &params);
    static void getCertificate(JSONP &output, const QHash <QString, QString> &params);

public:
    CertificateResponse();

    void generate(QString method, JSONP &output, const QHash <QString, QString> &params);
};

#endif // CERTIFICATERESPONSE_H
