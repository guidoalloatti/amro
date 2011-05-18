#ifndef QUERY_H
#define QUERY_H

#include <QString>
#include <QtSql>

class Query
{
    QString queryString;

public:
    Query & Select(QString);
    Query & From(QString);
    Query & Update(QString);
    Query & Set(QString);
    Query & Insert(QString);
    Query & Returning(QString);
    Query & Values(QString);
    Query & Delete();
    Query & Where(QString);
    Query & And(QString);
    Query & Or(QString);
    Query & OrderBy(QString, bool ascOrder = true);

    QSqlQuery prepare();
};

#endif // QUERY_H
