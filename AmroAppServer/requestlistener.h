#ifndef REQUESTLISTENER_H
#define REQUESTLISTENER_H

#include <QTcpServer>

class RequestListener : public QTcpServer
{
    Q_OBJECT

    void incomingConnection(int socketDescriptor);

public:
    RequestListener();
    void start();
    void stop();

signals:
    void requestAccepted();
    void failedListen();
    void finishedRequest();
    void listenerFinished();

public slots:
    void prepareToExit();
    void serverStart();
    void serverStop();
    void processRequestFinished();
};

#endif // REQUESTLISTENER_H
