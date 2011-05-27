#include "termicaltreatmentmapper.h"

#include "database.h"
#include <QtSql>

#include "query.h"

static const QString selectFields("id, date, image_path, observations");

TermicalTreatmentMapper::TermicalTreatmentMapper()
{
    this->tableName = "termicaltreatments";
}

QList <TermicalTreatment> TermicalTreatmentMapper::makeTTreatments(QSqlQuery &q)
{
        QList <TermicalTreatment> tts;

        q.exec();

        while (q.next())
        {
            TermicalTreatment tt;

            tt.id = q.value(0).toUInt();
            tt.date = q.value(1).toDate();
            tt.imagePath = q.value(2).toString();
            tt.observations = q.value(3).toString();

            tts << tt;
        }

        return tts;
}

bool TermicalTreatmentMapper::insert(const TermicalTreatment &tt)
{
    QSqlQuery q =
            Query().
            Insert(tableName).
            Values("DEFAULT, :date, :image_path, :observations").
            prepare();

    q.bindValue(":date", tt.date);
    q.bindValue(":image_path", tt.imagePath);
    q.bindValue(":observations", tt.observations);

    bool s = q.exec();

    qDebug() << q.lastError() << endl;

    return s;
}

bool TermicalTreatmentMapper::erase(const TermicalTreatment &tt)
{
    QSqlQuery q =
            Query().
            Delete().
            From(tableName).
            Where("id = :id").
            prepare();

    q.bindValue(":id", tt.id);

    return q.exec();
}

bool TermicalTreatmentMapper::update(const TermicalTreatment &tt)
{
    QSqlQuery q =
            Query().
            Update(tableName).
            Set("date = :date, image_path = :image_path, :observations").
            Where("id = :id").
            prepare();

    q.bindValue(":date", tt.date);
    q.bindValue(":image_path", tt.imagePath);
    q.bindValue(":observations", tt.observations);

    q.bindValue(":id", tt.id);

    return q.exec();
}

QList <TermicalTreatment> TermicalTreatmentMapper::get()
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      prepare();

    return makeTTreatments(query);
}

QList <TermicalTreatment> TermicalTreatmentMapper::get(quint32 id)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("id = :id").
                      prepare();

    query.bindValue(":id", id);

    return makeTTreatments(query);
}

QList <TermicalTreatment> TermicalTreatmentMapper::get(const QDate date)
{
    QSqlQuery query = Query().
                      Select(selectFields).
                      From(tableName).
                      Where("date = :date").
                      prepare();

    query.bindValue(":date", date);

    return makeTTreatments(query);
}

