#include "database.h"

#include <QtSql>

#include <QSharedPointer>

Database::Database()
{
    QString name;
    QTextStream tsName(&name);
    tsName << ((const void *) QThread::currentThread());

    this->name = name;

    //qDebug() << name + " quiere abrir la DB";

    if (!QSqlDatabase::database(name).isOpen())
    {
        QSqlDatabase db;
        //qDebug() << name + " DB cerrada";

        db = QSqlDatabase::addDatabase("QMYSQL", name);
        //qDebug() << name + " DB agregada";

        db.setHostName("localhost");
        db.setPort(3306);
        db.setDatabaseName("amro");
        db.setUserName("amro");
        db.setPassword("amr0s3rv3r");

        // HACER: ver que hacer en caso de que open falle, podria poner un metodo que me diga si es valida la DB
        //qDebug() << name + " DB a abrir";

        if (!db.open())
            qDebug() << db.lastError();        

    } else
        qDebug() << "The database is already opened";
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
