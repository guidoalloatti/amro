#include "database.h"

#include <QtSql>

#include <QSharedPointer>

Database::Database()
{
    QString name;
    QTextStream tsName(&name);
    tsName << ((const void *) QThread::currentThread());

    this->name = name;

    if (!QSqlDatabase::database(name).isOpen())
    {
        QSqlDatabase db;
        db = QSqlDatabase::addDatabase("QMYSQL", name);
        db.setHostName("localhost");
        db.setDatabaseName("amro");
        db.setUserName("amro");
        db.setPassword("amr0s3rv3r");

        // HACER: ver que hacer en caso de que open falle, podria poner un metodo que me diga si es valida la DB
        db.open();
    }
}

Database::~Database()
{
    QSqlDatabase::removeDatabase(name);
    QThread::currentThread()->setProperty("database", QVariant::Invalid);
}

Database* Database::getInstance()
{
    if (QThread::currentThread()->property("database") == QVariant::Invalid)
    {
        Database *db = new Database();

        QThread::currentThread()->setProperty("database", qVariantFromValue((void *) db));

        return db;
    }

    return (Database *) QThread::currentThread()->property("database").value<void *>();
}

QSqlDatabase Database::getQSqlDatabase()
{
    return QSqlDatabase::database(name);
}
