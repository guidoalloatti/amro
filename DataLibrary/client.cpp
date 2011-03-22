#include "client.h"

Client::Client(quint32 id, QString name)
{
    this->id = id;
    this->name = name;
}

Client::Client(quint32 id, QString name, QString initialNameCode, QString initialNumberSeq)
{
    this->id = id;
    this->name = name;
    if (!initialNameCode.isEmpty())
        this->nameCode = initialNameCode;

    if (!initialNumberSeq.isEmpty())
        this->sequenceNumber = initialNumberSeq;
}

void Client::setCurrentNameCode(QString code)
{
    if (code.isEmpty())
        return;

    this->codeHistory.append(this->nameCode);
    this->nameCode = code;
}

void Client::setCurrentSequenceNumber(QString number)
{
    if (number.isEmpty())
        return;

    this->sequenceNumber = number;
}

void Client::setName(QString name)
{
    this->name = name;
}

quint32 Client::getId() const{
    return this->id;
}

QString Client::getName() const
{
    return this->name;
}

QString Client::getSequenceNumber() const
{
    return this->sequenceNumber;
}

QString Client::getCurrentNameCode() const
{
    return this->nameCode;
}

QList <QString> Client::getCodeHistory() const
{
    return this->codeHistory;
}
