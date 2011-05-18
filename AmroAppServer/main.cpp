//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>

#include "requestlistener.h"
#include "../DataLibrary/certificate.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    Certificate c;
    QString err;
    c.generateCertificate(err);

    RequestListener rl;

    return a.exec();
}
