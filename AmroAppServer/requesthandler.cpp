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
    QTcpSocket socket;
    if (!socket.setSocketDescriptor(socketDescriptor))
        return;

    if (!socket.waitForConnected(20 * 1000))
        return;

    // HACER: todo esto mas robusto

    // HACER: tengo que leer hasta un "\r\n\r\n"
    if (!socket.canReadLine())
        socket.waitForReadyRead(20 * 1000);
    //QHttpRequestHeader header(socket.readAll().constData());
    QHttpRequestHeader header(socket.readLine());

    QUrl url(header.path());

    QHash <QString, QString> params;
    QPair <QString, QString> p;

    foreach (p, url.queryItems())
        params[p.first] = p.second;

    QTextStream output(&socket);

    ResponseMapper rm;
    rm.execute(params["method"], output, params);

    output.flush();
    socket.flush();

    socket.disconnectFromHost();

    if (socket.state() != QAbstractSocket::UnconnectedState)
        socket.waitForDisconnected();

    DataLib::shutdown();
}
