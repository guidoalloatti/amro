#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "requestlistener.h"

#include <QRunnable>
#include <QObject>

class RequestHandler : public QObject, public QRunnable
{
    Q_OBJECT

    int socketDescriptor;

public:
    RequestHandler(int socketDescriptor);
    void run();

signals:
    void requestDone();
};

#endif // REQUESTHANDLER_H
