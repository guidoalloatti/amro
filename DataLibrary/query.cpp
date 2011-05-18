#include "query.h"

#include "database.h"

Query & Query::Select(QString s)
{
    this->queryString += "SELECT " + s;
    return *this;
}

Query & Query::From(QString s)
{
    this->queryString += " FROM " + s;
    return *this;
}

Query & Query::Update(QString s)
{
    this->queryString += "UPDATE " + s;
    return *this;
}

Query & Query::Set(QString s)
{
    this->queryString += " SET " + s;
    return *this;
}

Query & Query::Insert(QString s)
{
    this->queryString += "INSERT INTO " + s;
    return *this;
}

Query & Query::Returning(QString s)
{
    this->queryString += " RETURNING " + s;
    return *this;
}

Query & Query::Values(QString s)
{
    this->queryString += " VALUES (" + s + ")";
    return *this;
}

Query & Query::Delete()
{
    this->queryString += "DELETE ";
    return *this;
}

Query & Query::Where(QString s)
{
    this->queryString += " WHERE " + s;
    return *this;
}

Query & Query::And(QString s)
{
    this->queryString += " AND " + s;
    return *this;
}

Query & Query::Or(QString s)
{
    this->queryString += " OR " + s;
    return *this;
}

Query & Query::OrderBy(QString key, bool ascOrder)
{
    this->queryString += " ORDER BY " + key;

    if (ascOrder)
        this->queryString += " ASC";
    else
        this->queryString += " DESC";

    return *this;
}

QSqlQuery Query::prepare()
{
    QSqlQuery q(Database::getInstance()->getQSqlDatabase());
    bool query_ok = q.prepare(this->queryString);

    // HACER: ver o sacar
    if (!query_ok)
    {
        qDebug() << "ERROR: can't prepare the query" << this->queryString << endl;
        qDebug() << q.lastError().text() << endl;
        Database::getInstance()->getQSqlDatabase().close();
    }

    Q_ASSERT(query_ok);
    return q;
}
