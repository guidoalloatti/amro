#include "client.h"

Client::Client(quint32 id, QString name)
{
    this->id = id;
    this->name = name;
}

Client::Client(quint32 id, QString name, QString initialNameCode, quint32 initialNumberSeq)
{
    this->id = id;
    this->name = name;
    if (!initialNameCode.isEmpty())
        this->nameCode = initialNameCode;

    this->currentSequence = initialNumberSeq;
}

void Client::setCurrentNameCode(QString code)
{
    if (code.isEmpty())
        return;

    this->codeHistory.append(this->nameCode);
    this->nameCode = code;
}

void Client::setCurrentSequenceNumber(quint32 number)
{
   this->currentSequence = number;
}

void Client::setSequenceDigits(quint32 digits)
{
   this->sequenceDigits = digits;
}

void Client::setName(QString name)
{
    this->name = name;
}

void Client::setAddress(QString address)
{
    this->address = address;
}

void Client::setCity(QString city)
{
    this->city = city;
}

void Client::setZip(QString zip)
{
    this->zip = zip;
}

void Client::setCountry(QString country)
{
    this->country = country;
}

void Client::setPhone(QString phone)
{
    this->phone = phone;
}

void Client::setTelefax(QString telefax)
{
    this->telefax = telefax;
}

void Client::setWebsite(QString website)
{
    this->website = website;
}

void Client::setId(quint32 id)
{
    this->id = id;
}

void Client::setCodeHistory(QList<QString> history)
{
    this->codeHistory << history;
}

quint32 Client::getId() const{
    return this->id;
}

QString Client::getName() const
{
    return this->name;
}

QString  Client::getAddress() const
{
    return this->address;
}

QString  Client::getCity() const
{
    return this->city;
}

QString  Client::getZip() const
{
    return this->zip;
}

QString  Client::getCountry() const
{
    return this->country;
}

QString  Client::getPhone() const
{
    return this->phone;
}

QString  Client::getTelefax() const
{
    return this->telefax;
}

QString  Client::getWebsite() const
{
    return this->website;
}

quint32 Client::getSequenceNumber() const
{
    return this->currentSequence;
}

quint32 Client::getSequenceDigits() const
{
    return this->sequenceDigits;
}

QString Client::getCurrentNameCode() const
{
    return this->nameCode;
}

QList <QString> Client::getCodeHistory() const
{
    return this->codeHistory;
}

void Client::IncrementSequenceNumber()
{
    this->currentSequence++;
}
