#include "certificateresponse.h"

CertificateResponse::CertificateResponse()
{
    methodTable["NewCertificate"] = &CertificateResponse::newCertificate;
    methodTable["DeleteCertificate"] = &CertificateResponse::deleteCertificate;
    methodTable["UpdateCertificate"] = &CertificateResponse::updateCertificate;
    methodTable["GetCertificate"] = &CertificateResponse::getCertificate;
}

void CertificateResponse::newCertificate(JSONP &output, const QHash <QString, QString> &params)
{

}

void CertificateResponse::deleteCertificate(JSONP &output, const QHash <QString, QString> &params)
{

}

void CertificateResponse::updateCertificate(JSONP &output, const QHash <QString, QString> &params)
{

}

void CertificateResponse::getCertificate(JSONP &output, const QHash <QString, QString> &params)
{

}

void CertificateResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
