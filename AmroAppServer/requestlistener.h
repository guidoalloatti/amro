#ifndef REQUESTLISTENER_H
#define REQUESTLISTENER_H

#include <QTcpServer>

class RequestListener : public QTcpServer
{
    Q_OBJECT

    void incomingConnection(int socketDescriptor);

public:
    RequestListener();
};

#endif // REQUESTLISTENER_H
