#include "requesthandler.h"

#include <QTextStream>
#include <QTcpSocket>
#include <QHttpRequestHeader>
#include <QFile>
#include <QUrl>

#include <QThread>

#include "responsemapper.h"

#include "../DataLibrary/datalib.h"

RequestHandler::RequestHandler(int socketDescriptor)
{
    this->socketDescriptor = socketDescriptor;
}

// HACER: ver bien el flujo de los datos en esta funcion
void RequestHandler::run()
{    
    QThread::currentThread()->setProperty("database", QVariant::Invalid);

    QTcpSocket socket;

    if (!socket.setSocketDescriptor(socketDescriptor)) {
        emit this->requestDone();
        return;
    }

    if (!socket.waitForConnected(20 * 1000)) {
        emit this->requestDone();
        return;
    }

    // HACER: todo esto mas robusto


    // HACER: tengo que leer hasta un "\r\n\r\n"
    if (!socket.canReadLine())
        socket.waitForReadyRead(20 * 1000);
    //QHttpRequestHeader header(socket.readAll().constData());

    QHttpRequestHeader header(socket.readLine());

    QUrl url(header.path());

    QHash <QString, QString> params;
    QPair <QString, QString> p;

    foreach (p, url.queryItems()) {
        p.second.replace('+', ' ');
        QByteArray decoded = QByteArray::fromPercentEncoding(QByteArray::fromPercentEncoding(p.second.toUtf8()));
        //QByteArray decoded = QByteArray::fromPercentEncoding(p.second.toUtf8());
        //qDebug() << decoded + " " + QString(decoded).toUtf8();
        params[p.first] = decoded.simplified();
    }

    QTextStream output(&socket);

    qDebug() << "Conexion exitosa " << params << endl;

    ResponseMapper rm;
    rm.execute(params["method"], output, params);

    output.flush();
    socket.flush();

    socket.disconnectFromHost();

    if (socket.state() != QAbstractSocket::UnconnectedState)
        socket.waitForDisconnected();

    DataLib::shutdown();
    emit this->requestDone();
}

