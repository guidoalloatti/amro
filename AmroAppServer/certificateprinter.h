#ifndef CERTIFICATEPRINTER_H
#define CERTIFICATEPRINTER_H

#include <QObject>
#include <QWebView>
#include <QDir>
#include <QMutex>

#include "../DataLibrary/certificate.h"

class CertificatePrinter : public QObject
{
    Q_OBJECT

    QWebView *view;
    QDir dir;
    QMutex mutex;
    Certificate current;

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
