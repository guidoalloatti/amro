//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QTextCodec>
#include <QDir>

#include "requestlistener.h"
#include "../DataLibrary/certificate.h"
#include "certificateprinter.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    /*QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(linuxCodec);
    QTextCodec::setCodecForCStrings(linuxCodec);
    QTextCodec::setCodecForLocale(linuxCodec);

    qRegisterMetaType<Certificate>("Certificate");

    CertificatePrinter *printer = CertificatePrinter::getPrinter();*/

    MainWindow w;
    w.show();

    //RequestListener rl;

    return a.exec();
}
