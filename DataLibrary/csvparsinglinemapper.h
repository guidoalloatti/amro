#ifndef CSVPARSINGLINEMAPPER_H
#define CSVPARSINGLINEMAPPER_H

#include "csvparsingline.h"
#include "query.h"


class DATALIBSHARED_EXPORT CSVParsingLineMapper
{
    QString tableName;

    QList <CSVParsingLine> makeCSVParsingLines(QSqlQuery &q);

public:
    CSVParsingLineMapper();
    bool insert(const CSVParsingLine &pl);
    bool update(const CSVParsingLine &pl);
    bool erase(const CSVParsingLine &pl);
    QList <CSVParsingLine> get(QVariantHash filters, QString order);
};

#endif // CSVPARSINGLINEMAPPER_H
