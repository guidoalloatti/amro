//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>

#include "requestlistener.h"
#include "../DataLibrary/certificate.h"
#include "certificateprinter.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    qRegisterMetaType<Certificate>("Certificate");

    CertificatePrinter *printer = CertificatePrinter::getPrinter();

    RequestListener rl;

    return a.exec();
}
