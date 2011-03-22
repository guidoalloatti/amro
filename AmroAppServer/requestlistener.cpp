#include "requestlistener.h"

#include "requesthandler.h"

#include <QCoreApplication>
#include <QThreadPool>

#include <QVariant> // Sacar

void RequestListener::incomingConnection(int socketDescriptor)
{
    QThreadPool::globalInstance()->start(new RequestHandler(socketDescriptor));
}

RequestListener::RequestListener()
{
    // HACER: poner otro puerto mas apropiado
    // HACER: guardar todas las settings en algun lugar mas apropiado (un archivo de texto)
    int port = 8080;

    if (!listen(QHostAddress::Any, port))
    {
        qDebug() << "ERROR: can't bind port" << port;
        // HACER: ver por que no sale con esto, aparentemente porque todavia no
        // entro al main loop
        QCoreApplication::quit();
    }

    QThreadPool::globalInstance()->setMaxThreadCount(32);
}
