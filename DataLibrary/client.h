#ifndef CLIENT_H
#define CLIENT_H

#include "DataLib_global.h"

#include <QString>
#include <QList>

class DATALIBSHARED_EXPORT Client
{
public:
    Client() {}
    Client(quint32 id, QString name);
    Client(quint32 id, QString name, QString initialNameCode, QString initialNumberSeq);

    void setCurrentNameCode(QString code);
    void setCurrentSequenceNumber(QString number);
    void setName(QString name);

    quint32 getId() const;
    QString getName() const;
    QString getSequenceNumber() const;
    QString getCurrentNameCode() const;
    QList <QString> getCodeHistory() const;

private:
    quint32 id;
    QString  name, address, city, zip, country, phone, telefax, website;
    QString nameCode, sequenceNumber;
    QList <QString> codeHistory;

    friend class ClientMapper;
};

#endif // CLIENT_H
