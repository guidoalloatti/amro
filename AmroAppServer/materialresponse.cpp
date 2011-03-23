#include "materialresponse.h"

MaterialResponse::MaterialResponse()
{
    methodTable["NewMaterial"] = &MaterialResponse::newMaterial;
    methodTable["DeleteMaterial"] = &MaterialResponse::deleteMaterial;
    methodTable["UpdateMaterial"] = &MaterialResponse::updateMaterial;
    methodTable["GetMaterial"] = &MaterialResponse::getMaterial;
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
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
