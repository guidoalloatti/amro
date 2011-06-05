#include "requestlistener.h"

#include "requesthandler.h"

#include <QCoreApplication>
#include <QThreadPool>
#include <QTcpSocket>

#include <QVariant> // Sacar

void RequestListener::incomingConnection(int socketDescriptor)
{
    RequestHandler *handler = new RequestHandler(socketDescriptor);
    //QTcpSocket socket;
    //socket.setSocketDescriptor(socketDescriptor);
    connect(handler, SIGNAL(requestDone()), this, SLOT(processRequestFinished()));
    QThreadPool::globalInstance()->start(handler);
    emit this->requestAccepted();
}

RequestListener::RequestListener()
{
    /*// HACER: poner otro puerto mas apropiado
    // HACER: guardar todas las settings en algun lugar mas apropiado (un archivo de texto)
    int port = 8080;

    if (!listen(QHostAddress::Any, port))
    {
        qDebug() << "ERROR: can't bind port" << port;
        // HACER: ver por que no sale con esto, aparentemente porque todavia no
        // entro al main loop
        QCoreApplication::quit();
    }

    QThreadPool::globalInstance()->setMaxThreadCount(32);*/
    //CertificatePrinter *printer = CertificatePrinter::getPrinter();

}

void RequestListener::start()
{
    // HACER: poner otro puerto mas apropiado
    // HACER: guardar todas las settings en algun lugar mas apropiado (un archivo de texto)
    int port = 8080;

    if (!listen(QHostAddress::Any, port))
    {
        qDebug() << "ERROR: can't bind port" << port;
        // HACER: ver por que no sale con esto, aparentemente porque todavia no
        // entro al main loop
        //QCoreApplication::quit();
        emit this->failedListen();
        return;
    }

    QThreadPool::globalInstance()->setMaxThreadCount(32);
}

void RequestListener::stop()
{
    close();
}

void RequestListener::serverStart()
{
    start();
}

void RequestListener::serverStop() {
    stop();
}

void RequestListener::processRequestFinished()
{
    emit this->finishedRequest();
}

void RequestListener::prepareToExit()
{
    stop();
    emit this->listenerFinished();
}
