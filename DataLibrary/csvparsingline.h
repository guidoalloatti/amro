#ifndef CSVPARSINGLINE_H
#define CSVPARSINGLINE_H

#include "DataLib_global.h"
#include "client.h"
#include "material.h"

#include <QString>


class DATALIBSHARED_EXPORT CSVParsingLine
{    
public:
    CSVParsingLine();

    void setNumProbeta(QString numProbeta);
    void setId(quint32 id);
    void setOrdenCompra(quint32 ordenCompra);
    void setMaterial(Material m);
    void setClient(Client m);
    void setDescription(QString desc);

    QString getNumProbeta() const;
    quint32 getId() const;
    quint32 getOrdenCompra() const;
    Material getMaterial() const;
    Client getClient() const;
    QString getDescription() const;

private:
    QString numProbeta;
    quint32 ordenCompra;
    Material material;
    Client client;
    QString description;
    quint32 id;

    friend class CSVParsingLineMapper;
};

#endif // CSVPARSINGLINE_H
