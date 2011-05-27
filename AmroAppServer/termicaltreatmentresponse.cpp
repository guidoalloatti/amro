#include "termicaltreatmentresponse.h"

#include "../DataLibrary/usermapper.h"
#include "../DataLibrary/termicaltreatmentmapper.h"


TermicalTreatmentResponse::TermicalTreatmentResponse()
{
    methodTable["NewTT"] = &TermicalTreatmentResponse::newTTreatment;
    methodTable["DeleteTT"] = &TermicalTreatmentResponse::deleteTTreatment;
    methodTable["UpdateTT"] = &TermicalTreatmentResponse::updateTTreatment;
    methodTable["GetTT"] = &TermicalTreatmentResponse::getTTreatment;
}

static bool hasPermission(QString email, QString password, QString permission)
{
    QList <User> users = UserMapper().get(email, password);

    if (users.empty())
        return false;

    return users[0].hasPrivileges(permission);
}

/* Nombre del cliente debe ser UNIQUE */

void TermicalTreatmentResponse::newTTreatment(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "NewTT");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "TT_INSERT"))
    {
        TermicalTreatment tt;

        int day = params.value("day", "0").toUInt();
        int month = params.value("month", "0").toUInt();
        int year = params.value("year", "0").toUInt();

        QDate date;
        if (!day || !month || !year)
            date = QDate::currentDate();
        else
            date.setDate(year, month, day);

        if (!date.isValid()) {
            output.add("date", "invalid");
            output.add("success", false);
            return;
        }

        tt.setDate(date);
        tt.setImagePath(params.value("path", "").toUtf8());
        tt.setObservations(params.value("observations", "").toUtf8());

        success = TermicalTreatmentMapper().insert(tt);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void TermicalTreatmentResponse::deleteTTreatment(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteTT");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "TT_DELETE"))
    {
        quint32 id = params.value("id", "").toUInt();

        TermicalTreatment tt;
        tt.setId(id);
        success = TermicalTreatmentMapper().erase(tt);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void TermicalTreatmentResponse::updateTTreatment(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "UpdateClient");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "TT_UPDATE"))
    {
        TermicalTreatment tt;

        tt.setId(params.value("id", "").toUInt());

        int day = params.value("day", "0").toUInt();
        int month = params.value("month", "0").toUInt();
        int year = params.value("year", "0").toUInt();

        QDate date;
        if (!day || !month || !year)
            date = QDate::currentDate();
        else
            date.setDate(year, month, day);

        if (!date.isValid()) {
            output.add("date", "invalid");
            output.add("success", false);
            return;
        }

        tt.setDate(date);
        tt.setImagePath(params.value("path", "").toUtf8());


        success = TermicalTreatmentMapper().update(tt);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

QVariantList serializeTTs(QList <TermicalTreatment> termicalTreatments)
{
    QVariantList serializedTTs;

    foreach(TermicalTreatment tt, termicalTreatments) {
        QVariantHash ttProperties;

        ttProperties["id"] = tt.getId();
        ttProperties["date"] = tt.getDate().toString("dd-MM-yyyy");
        ttProperties["path"] = tt.getImagePath();
        ttProperties["observations"] = tt.getObservations();

        serializedTTs << ttProperties;
    }

    return serializedTTs;
}

void TermicalTreatmentResponse::getTTreatment(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "GetTT");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "TT_LIST")) {
        QList <TermicalTreatment> tts;
        if (params.keys().contains("id"))
            tts = TermicalTreatmentMapper().get(params.value("id").toUInt());
        else if (params.keys().contains("year") && params.keys().contains("month") && params.keys().contains("day")) {
            int day = params.value("day", "0").toUInt();
            int month = params.value("month", "0").toUInt();
            int year = params.value("year", "0").toUInt();
            QDate date(year, month, day);
            tts = TermicalTreatmentMapper().get(date);
        } else
            tts = TermicalTreatmentMapper().get();

        success = true;
        output.add("tts", serializeTTs(tts));
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void TermicalTreatmentResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
