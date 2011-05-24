#ifndef CERTIFICATEGENERATOR_H
#define CERTIFICATEGENERATOR_H

#include <QObject>
#include <QMutex>

#include "../DataLibrary/certificate.h"

class CertificateGenerator : public QObject
{
    Q_OBJECT

    bool requestCompleted;
    bool requestStatus;
    QMutex mutex;

public:
    CertificateGenerator();

    bool generate(Certificate &c);

signals:
    void requestGeneration(Certificate c);

public slots:
    void requestIsCompleted(bool status);
};

#endif // CERTIFICATEGENERATOR_H
