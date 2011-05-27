#ifndef CERTIFICATEPRINTER_H
#define CERTIFICATEPRINTER_H

#include <QObject>
#include <QWebView>

#include "../DataLibrary/certificate.h"

class CertificatePrinter : public QObject
{
    Q_OBJECT

    QWebView *view;

    static CertificatePrinter *pinstance;

protected:
    CertificatePrinter();

public:
    static CertificatePrinter* getPrinter();

    QWebView* getView();

signals:
    void requestDone(bool status);

public slots:
    void generate(Certificate c);
    void print(bool ok);
};

#endif // CERTIFICATEPRINTER_H
