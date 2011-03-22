#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "requestlistener.h"

#include <QRunnable>

class RequestHandler : public QRunnable
{
    int socketDescriptor;

public:
    RequestHandler(int socketDescriptor);
    void run();
};

#endif // REQUESTHANDLER_H
