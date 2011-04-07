#ifndef CLIENT_H
#define CLIENT_H

#include "DataLib_global.h"

#include <QString>
#include <QList>

class DATALIBSHARED_EXPORT Client
{
public:
    Client() { sequenceDigits = 3; currentSequence = 0;}
    Client(quint32 id, QString name);
    Client(quint32 id, QString name, QString initialNameCode, quint32 initialNumberSeq);

    void setName(QString name);
    void setAddress(QString address);
    void setCity(QString city);
    void setZip(QString zip);
    void setCountry(QString country);
    void setPhone(QString phone);
    void setTelefax(QString telefax);
    void setWebsite(QString website);
    void setId(quint32 id);

    quint32 getId() const;
    QString getName() const;
    QString getAddress() const;
    QString getCity() const;
    QString getZip() const;
    QString getCountry() const;
    QString getPhone() const;
    QString getTelefax() const;
    QString getWebsite() const;

    void setCurrentNameCode(QString code);
    void setSequenceDigits(quint32 digits);
    void setCurrentSequenceNumber(quint32 number);

    quint32 getSequenceNumber() const;
    quint32 getSequenceDigits() const;
    QString getCurrentNameCode() const;

    void setCodeHistory(QList<QString> history);
    QList <QString> getCodeHistory() const;

    void IncrementSequenceNumber();


private:
    quint32 id;
    quint32 sequenceDigits, currentSequence;
    QString  name, address, city, zip, country, phone, telefax, website;
    QString nameCode;
    QList <QString> codeHistory;


    friend class ClientMapper;
};

#endif // CLIENT_H
