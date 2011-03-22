#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QObject>

// HACER: agregar los metodos commit, rollback y transaction en vez de usarlos por QSqlDatabase

class Database
{
    QString name;

public:
    Database();
    ~Database();
    static Database* getInstance();
    QSqlDatabase getQSqlDatabase(); // HACER: que sea const
};

#endif // DATABASE_H
