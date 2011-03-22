#include "materialresponse.h"

MaterialResponse::MaterialResponse()
{
    methodTable["NewMaterial"] = &newMaterial;
    methodTable["DeleteMaterial"] = &deleteMaterial;
    methodTable["UpdateMaterial"] = &updateMaterial;
    methodTable["GetMaterial"] = &getMaterial;
}

void MaterialResponse::login(JSONP &output, const QHash <QString, QString> &params)
{

}

void MaterialResponse::newMaterial(JSONP &output, const QHash <QString, QString> &params)
{

}

void MaterialResponse::deleteMaterial(JSONP &output, const QHash <QString, QString> &params)
{

}

void MaterialResponse::updateMaterial(JSONP &output, const QHash <QString, QString> &params)
{

}

void MaterialResponse::getMaterial(JSONP &output, const QHash <QString, QString> &params)
{

}

void MaterialResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, QHash <QString, QString> &) = methodTable.value(method);

    if (f != 0)
        return (*f)(output, params);
}
