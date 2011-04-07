#include "materialresponse.h"
#include "../DataLibrary/usermapper.h"
#include "../DataLibrary/materialmapper.h"

MaterialResponse::MaterialResponse()
{
    methodTable["NewMaterial"] = &MaterialResponse::newMaterial;
    methodTable["DeleteMaterial"] = &MaterialResponse::deleteMaterial;
    methodTable["UpdateMaterial"] = &MaterialResponse::updateMaterial;
    methodTable["GetMaterial"] = &MaterialResponse::getMaterial;
}

static bool hasPermission(QString email, QString password, QString permission)
{
    QList <User> users = UserMapper().get(email, password);

    if (users.empty())
        return false;

    return users[0].hasPrivileges(permission);
}

void MaterialResponse::newMaterial(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "NewMaterial");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "MATERIAL_INSERT"))
    {
        Material m;

        m.setName(params.value("name", "").toUtf8());
        m.setDescription(params.value("description", "").toUtf8());

        /*
         * %20 es el espacio
         * %3D es el =
         */
        QByteArray cLimits = QByteArray::fromPercentEncoding(params.value("chlimits", "").toUtf8()).simplified();
        foreach(QByteArray limit, cLimits.split(' ')) {
            QList <QByteArray> measure = limit.split('=');
            m.setChemicalValue(measure[0], measure[1].replace(',', ".").toDouble());
        }

        QByteArray mLimits = QByteArray::fromPercentEncoding(params.value("mlimits", "").toUtf8()).simplified();
        foreach(QByteArray limit, mLimits.split(' ')) {
            QList <QByteArray> measure = limit.split('=');
            m.setMechanicalValue(measure[0], measure[1].replace(',', ".").toDouble());
        }

        success = MaterialMapper().insert(m);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void MaterialResponse::deleteMaterial(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteMaterial");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "MATERIAL_DELETE"))
    {
        Material m;

        m.setId(params.value("id", "").toUInt());

        success = MaterialMapper().erase(m);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void MaterialResponse::updateMaterial(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "UpdateMaterial");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "MATERIAL_UPDATE"))
    {
        Material m;

        m.setId(params.value("id", "").toUInt());
        m.setName(params.value("name", "").toUtf8());
        m.setDescription(params.value("description", "").toUtf8());

        /*
         * %20 es el espacio
         * %3D es el =
         */
        QByteArray cLimits = QByteArray::fromPercentEncoding(params.value("chlimits", "").toUtf8()).simplified();
        foreach(QByteArray limit, cLimits.split(' ')) {
            QList <QByteArray> measure = limit.split('=');
            m.getChemicalLimit().setValue(measure[0], measure[1].replace(',', ".").toDouble());
        }

        QByteArray mLimits = QByteArray::fromPercentEncoding(params.value("mlimits", "").toUtf8()).simplified();
        foreach(QByteArray limit, mLimits.split(' ')) {
            QList <QByteArray> measure = limit.split('=');
            m.getMechanicalLimit().setValue(measure[0], measure[1].replace(',', ".").toDouble());
        }

        success = MaterialMapper().update(m);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

QVariantList serializeMaterials(QList <Material> materials)
{
    QVariantList serializedMaterials;

    foreach(Material m, materials) {
        QVariantHash materialProperties;

        materialProperties["id"] = m.getId();
        materialProperties["name"] = m.getName();
        materialProperties["description"] = m.getDescription();

        materialProperties["chlimits"] = m.getChemicalLimit().print();
        materialProperties["mlimits"] = m.getMechanicalLimit().print();

        serializedMaterials << materialProperties;
    }

    return serializedMaterials;
}

void MaterialResponse::getMaterial(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "GetMaterial");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "MATERIAL_LIST"))
    {
        QList <Material> materials;
        if (params.keys().contains("id"))
             materials = MaterialMapper().get(params.value("id").toUInt());
        else
             materials = MaterialMapper().get();

        success = true;
        output.add("materials", serializeMaterials(materials));
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void MaterialResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
