#include <QtCore/QCoreApplication>

#include "requestlistener.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RequestListener rl;

    return a.exec();
}
