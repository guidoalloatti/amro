#include "analysisresponse.h"
#include "../DataLibrary/clientmapper.h"
#include "../DataLibrary/usermapper.h"
#include "../DataLibrary/materialmapper.h"
#include "../DataLibrary/mechanicalanalysismapper.h"
#include "../DataLibrary/chemicalanalysismapper.h"
#include "../DataLibrary/termicaltreatmentmapper.h"

#include <QFile>
#include <QStringList>

AnalysisResponse::AnalysisResponse()
{
    methodTable["ParseCA"] = &AnalysisResponse::parseCA;
    methodTable["DeleteCA"] = &AnalysisResponse::deleteCA;
    methodTable["AttachTT"] = &AnalysisResponse::addTTtoCA;
    methodTable["CheckCA"] = &AnalysisResponse::checkCA;
    methodTable["LoadMA"] = &AnalysisResponse::loadMA;
    methodTable["DeleteMA"] = &AnalysisResponse::deleteMA;
    methodTable["GetMA"] = &AnalysisResponse::getMA;
}

static bool hasPermission(QString email, QString password, QString permission)
{
    QList <User> users = UserMapper().get(email, password);

    if (users.empty())
        return false;

    return users[0].hasPrivileges(permission);
}

static const QStringList columns = QStringList() << "probeta" << "fecha" << "calidad";

static bool parseCSV(QFile *file, QVariantHash &error)
{
    QTextStream stream (file);
    QString line;
    int lineNumber = 0;
    QHash <QString, quint32> headerIndexMapper;
    QHash <QString, quint32> measuresIndexMapper;

    while(!stream.atEnd()) {
        line = stream.readLine();

        QStringList fields;
        fields = line.split(';');        

        lineNumber++;
        if (lineNumber == 1) {
            int index = 0, measuresMatched = 0, columnsMatched = 0;
            foreach(QString field, fields) {
                if (columns.contains(field, Qt::CaseInsensitive)) {
                    headerIndexMapper[field.toLower()] = index;
                    columnsMatched++;
                } else if (chProperties.contains(field, Qt::CaseInsensitive)) {
                    measuresIndexMapper[field.toLower()] = index;
                    measuresMatched++;
                }

                index++;
            }

            if (columns.length() != columnsMatched ||
                chProperties.length()-1 != measuresMatched) {
                error[QString::number(lineNumber)] = "Information Incomplete";
                return false;
            }

            continue;
        }

        ChemicalAnalysis ca;

        QList <Material> materials;
        materials = MaterialMapper().get(fields.at(headerIndexMapper["calidad"]));
        if (materials.length() == 1)
            ca.setMaterial(materials.first());
        else {
            error[QString::number(lineNumber)] = "Material Unknown";
            continue;
        }

        QString probeta = fields.at(headerIndexMapper["probeta"]);
        QRegExp numProbetaFormat("([a-z|A-Z]+)(\\s*|\\-)(\\d+)");

        if (numProbetaFormat.exactMatch(probeta))
            ca.setNumProbeta(numProbetaFormat.cap(1).toLower() + numProbetaFormat.cap(3));
        else {
            error[QString::number(lineNumber)] = "Wrong Probeta Format";
            continue;
        }

        QDate newDate;
        newDate = newDate.fromString(fields.at(headerIndexMapper["fecha"]), "dd/MM/yyyy");

        if (!newDate.isValid()) {
            error[QString::number(lineNumber)] = "Wrong Fecha Format";
            continue;
        }
        ca.setDate(newDate);

        // Hasta ahora es esta fecha, luego se va a poder cambiar a través de un abm
        //ca.setTTDate(newDate);

        QVariantHash measures;
        foreach(QString measure, measuresIndexMapper.keys()) {
            QString value = fields.at(measuresIndexMapper[measure]);
            measures[measure] = QVariantList() << QVariant(value.toDouble()) << 0;
        }

        ca.setMeasures(ChemicalMeasure(measures));

        if (!ChemicalAnalysisMapper().insert(ca))
            error[QString::number(lineNumber)] = "Insert Error";
    }

    return true;
}

void AnalysisResponse::parseCA(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "ParseCA");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "PARSE_CA")) {
        QString filePath = params.value("filepath", "").toUtf8();

        QFile csvFile;

        csvFile.setFileName(filePath);
        if (csvFile.open(QFile::ReadOnly)) {
            QVariantHash error;
            if (parseCSV(&csvFile, error))
                success = true;
            output.add("errors", error);
            csvFile.close();
        } else
            output.add("filepath", "failed");

    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void AnalysisResponse::deleteCA(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteCA");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "CA_DELETE"))
    {
        quint32 id = params.value("id", "").toUInt();

        ChemicalAnalysis ca;
        ca.setId(id);
        success = ChemicalAnalysisMapper().erase(ca);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void AnalysisResponse::addTTtoCA(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "AttachTT");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "TT_CA_ATTACH"))
    {
        TermicalTreatment termicalTreatment;

        QList <TermicalTreatment> tts = TermicalTreatmentMapper().get(params.value("ttreatment_id", "0").toUInt());
        if (tts.length() == 1) {
            termicalTreatment = tts.first();
        } else {
            output.add("error", "bad tt id");
            return;
        }

        ChemicalAnalysis ca;

        QVariantHash filters;
        filters["id"] = params.value("id", "0").toUInt();

        QList <ChemicalAnalysis> cas;
        cas = ChemicalAnalysisMapper().get(filters);
        if (cas.length() == 1)
            ca = cas.first();
        else {
            output.add("error", "chemical analysis does not exist");
            return;
        }

        ca.setTermicalTreatment(termicalTreatment);

        success = ChemicalAnalysisMapper().update(ca);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}


QVariantList serializeCAnalysis(QList <ChemicalAnalysis> analysis)
{
    QVariantList serializedAnalysys;

    foreach(ChemicalAnalysis ca, analysis) {
        QVariantHash analysysProperties;

        analysysProperties["id"] = ca.getId();
        analysysProperties["numprobeta"] = ca.getNumProbeta();
        analysysProperties["material_id"] = ca.getMaterial().getId();
        analysysProperties["date"] = ca.getDate();
        //analysysProperties["ttdate"] = ca.GetTTDate();
        analysysProperties["ttreatment_id"] = ca.GetTermicalTreatment().getId();
        analysysProperties["chemicalanalysis"] = ca.getMeasures().print();

        serializedAnalysys << analysysProperties;
    }

    return serializedAnalysys;
}


void AnalysisResponse::checkCA(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "CheckCA");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "GET_CA")) {
        QList <ChemicalAnalysis> cas;
        QVariantHash filters;

        int year = params.value("year", "0").toUInt();
        int month = params.value("month", "0").toUInt();
        int day = params.value("day", "0").toUInt();

        if (year && month && day)
            filters["date"] = QDate(year, month, day);

        if (params.contains("material_id"))
            filters["material_id"] = params.value("material_id").toUInt();

        if (params.contains("numprobeta"))
            filters["numprobeta"] = params.value("numprobeta");

        cas = ChemicalAnalysisMapper().get(filters);

        success = true;
        output.add("CAnalysis", serializeCAnalysis(cas));
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void AnalysisResponse::loadMA(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "LoadMA");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "LOAD_MA")) {
        MechanicalAnalysis ma;

        quint32 material_id = params.value("material_id", "").toUInt();
        QList <Material> materials = MaterialMapper().get(material_id);
        if (materials.length() == 1)
            ma.setMaterial(materials.first());
        else {
            output.add("material_id", material_id);
            output.add("success", success);
            return;
        }

        ma.setDate(QDate::currentDate());

        /*
         * %20 es el espacio
         * %3D es el =
         */
        /*QByteArray mAnalysis = params.value("mechanicalanalysis", "").toUtf8().simplified();
        foreach(QByteArray analysis, mAnalysis.split('+')) {
            QList <QByteArray> measure = analysis.split('=');
            ma.setMeasureValue(measure[0], measure[1].replace(',', ".").toDouble());
        }*/

        QByteArray mAnalysis = params.value("mechanicalanalysis", "").toUtf8().simplified();
        foreach(QByteArray limit, mAnalysis.split('+')) {
            QList <QByteArray> measure = limit.split('=');
            int min = 0;
            foreach(QByteArray value, measure[1].replace(',', ".").split('-')) {
                if (!min)
                    ma.setMeasureMaxValue(measure[0].simplified(), value.toDouble());
                else
                    ma.setMeasureMinValue(measure[0].simplified(), value.toDouble());

                min++;

                if (min > 2) {
                    output.add("error", "Bad Formatted Mechanical Measures Values");
                    output.add("success", false);
                    return;
                }

            }
        }


        success = MechanicalAnalysisMapper().insert(ma);
    }

    output.add("success", success);
}

void AnalysisResponse::deleteMA(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteMA");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "MA_DELETE"))
    {
        quint32 id = params.value("id", "").toUInt();

        MechanicalAnalysis ma;
        ma.setId(id);
        success = MechanicalAnalysisMapper().erase(ma);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

QVariantList serializeMAnalysis(QList <MechanicalAnalysis> analysis)
{
    QVariantList serializedAnalysys;

    foreach(MechanicalAnalysis ma, analysis) {
        QVariantHash analysysProperties;

        analysysProperties["id"] = ma.getId();
        analysysProperties["material_id"] = ma.getMaterial().getId();
        analysysProperties["date"] = ma.getDate();
        analysysProperties["mechanicalanalysis"] = ma.getMeasures().print();

        serializedAnalysys << analysysProperties;
    }

    return serializedAnalysys;
}

void AnalysisResponse::getMA(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "GetMA");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "GET_MA")) {
        QList <MechanicalAnalysis> mas;
        QVariantHash filters;

        int year = params.value("year", "0").toUInt();
        int month = params.value("month", "0").toUInt();
        int day = params.value("day", "0").toUInt();

        if (year && month && day)
            filters["date"] = QDate(year, month, day);


        if (params.contains("material_id"))
            filters["material_id"] = params.value("material_id").toUInt();

        if (params.contains("id"))
            filters["id"] = params.value("id").toUInt();

        QString order = params.value("order", "id").toUtf8();
        mas = MechanicalAnalysisMapper().get(filters, order);

        success = true;
        output.add("MAnalysis", serializeMAnalysis(mas));
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void AnalysisResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}

