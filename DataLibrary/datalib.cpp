#include "datalib.h"

#include "database.h"
#include <QtSql>

DataLib::DataLib() {}

bool DataLib::transaction()
{
    return Database::getInstance()->getQSqlDatabase().transaction();
}

bool DataLib::commit()
{
    return Database::getInstance()->getQSqlDatabase().commit();
}

bool DataLib::rollback()
{
    return Database::getInstance()->getQSqlDatabase().rollback();
}

void DataLib::shutdown()
{
    delete Database::getInstance();
}
