#include "certificateresponse.h"

CertificateResponse::CertificateResponse()
{
    methodTable["NewCertificate"] = &newCertificate;
    methodTable["DeleteCertificate"] = &deleteCertificate;
    methodTable["UpdateCertificate"] = &updateCertificate;
    methodTable["GetCertificate"] = &getCertificate;
}

void CertificateResponse::login(JSONP &output, const QHash <QString, QString> &params)
{

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
    void (*f) (JSONP &, QHash <QString, QString> &) = methodTable.value(method);

    if (f != 0)
        return (*f)(output, params);
}
