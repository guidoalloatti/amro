#include "csvparsingline.h"

CSVParsingLine::CSVParsingLine()
{
}

void CSVParsingLine::setNumProbeta(QString numProbeta)
{
    this->numProbeta = numProbeta;
}

void CSVParsingLine::setOrdenCompra(quint32 ordenCompra)
{
    this->ordenCompra = ordenCompra;
}

void CSVParsingLine::setId(quint32 id)
{
    this->id = id;
}

void CSVParsingLine::setMaterial(Material m)
{
    this->material = m;
}

void CSVParsingLine::setClient(Client c)
{
    this->client = c;
}

void CSVParsingLine::setDescription(QString desc)
{
    this->description = desc;
}

QString CSVParsingLine::getNumProbeta() const
{
    return this->numProbeta;
}

quint32 CSVParsingLine::getId() const
{
    return this->id;
}

quint32 CSVParsingLine::getOrdenCompra() const
{
    return this->ordenCompra;
}

Material CSVParsingLine::getMaterial() const
{
    return this->material;
}
Client CSVParsingLine::getClient() const
{
    return this->client;
}

QString CSVParsingLine::getDescription() const
{
    return this->description;
}

