#include "certificateresponse.h"
#include "../DataLibrary/certificatemapper.h"
#include "../DataLibrary/usermapper.h"
#include "../DataLibrary/materialmapper.h"
#include "../DataLibrary/clientmapper.h"

CertificateResponse::CertificateResponse()
{
    methodTable["NewCertificate"] = &CertificateResponse::newCertificate;
    methodTable["DeleteCertificate"] = &CertificateResponse::deleteCertificate;
    //methodTable["UpdateCertificate"] = &CertificateResponse::updateCertificate;
    methodTable["GetCertificate"] = &CertificateResponse::getCertificate;
}

static bool hasPermission(QString email, QString password, QString permission)
{
    QList <User> users = UserMapper().get(email, password);

    if (users.empty())
        return false;

    return users[0].hasPrivileges(permission);
}

void CertificateResponse::newCertificate(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "NewCertificate");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    QList <User> users = UserMapper().get(email, password);

    bool success = false;

    while (!users.empty() && users[0].hasPrivileges("CERTIFICATE_INSERT"))
    {
        Certificate c;
        c.setProtN(params.value("protn", "").toUtf8());
        c.setOrdenCompra(params.value("ordencompra", "").toUtf8());
        c.setObservations(params.value("observations", "").toUtf8());
        c.setDescription(params.value("description", "").toUtf8());
        c.setImagePath(params.value("termicopath", "").toUtf8());

        quint32 client_id = params.value("client_id", "").toUInt();
        QList <Client> clients = ClientMapper().get(client_id);
        if (clients.length() == 1)
            c.setClient(clients.first());
        else {
            output.add("client_id", client_id);
            break;
        }

        c.setNumProbeta(c.getClient().getCurrentNameCode() + c.getClient().getSequenceNumber());

        quint32 material_id = params.value("material_id", "").toUInt();
        QList <Material> materials = MaterialMapper().get(material_id);
        if (materials.length() == 1)
            c.setMaterial(materials.first());
        else {
            output.add("material_id", material_id);
            break;
        }

        quint32 approver_id = params.value("approver_id", "").toUInt();
        QList <User> approvers = UserMapper().get(approver_id);
        if (approvers.length() == 1)
            c.setApprover(approvers.first());
        else {
            output.add("approver_id", approver_id);
            break;
        }

        quint32 reviewer_id = params.value("reviewer_id", "").toUInt();
        QList <User> reviewers = UserMapper().get(reviewer_id);
        if (reviewers.length() == 1)
            c.setReviewer(reviewers.first());
        else {
            output.add("reviewer_id", reviewer_id);
            break;
        }

        output.add("performer_id", users[0].getId());

        c.setDate(QDate::currentDate());

        /*
         * %20 es el espacio
         * %3D es el =
         */
        /*QByteArray cAnalysis = params.value("chemicalanalysis", "").toUtf8().simplified();
        foreach(QByteArray analysis, cAnalysis.split('+')) {
            QList <QByteArray> measure = analysis.split('=');
            c.setChemicalValue(measure[0], measure[1].replace(',', ".").toDouble());
        }*/
        QByteArray cAnalysis = params.value("chemicalanalysis", "").toUtf8().simplified();
        foreach(QByteArray limit, cAnalysis.split('+')) {
            QList <QByteArray> measure = limit.split('=');
            int min = 0;
            foreach(QByteArray value, measure[1].replace(',', ".").split('-')) {
                if (!min)
                    c.setChemicalMaxValue(measure[0].simplified(), value.toDouble());
                else
                    c.setChemicalMinValue(measure[0].simplified(), value.toDouble());

                min++;

                if (min > 2) {
                    output.add("error", "Bad Formatted Measures Value");
                    output.add("success", false);
                    return;
                }

            }
        }

        /*QByteArray mAnalysis = params.value("mechanicalanalysis", "").toUtf8().simplified();
        foreach(QByteArray analysis, mAnalysis.split('+')) {
            QList <QByteArray> measure = analysis.split('=');
            c.setMechanicalValue(measure[0], measure[1].replace(',', ".").toDouble());
        }*/
        QByteArray mAnalysis = params.value("mechanicalanalysis", "").toUtf8().simplified();
        foreach(QByteArray limit, mAnalysis.split('+')) {
            QList <QByteArray> measure = limit.split('=');
            int min = 0;
            foreach(QByteArray value, measure[1].replace(',', ".").split('-')) {
                if (!min)
                    c.setMechanicalMaxValue(measure[0].simplified(), value.toDouble());
                else
                    c.setMechanicalMinValue(measure[0].simplified(), value.toDouble());

                min++;

                if (min > 2) {
                    output.add("error", "Bad Formatted Measures Value");
                    output.add("success", false);
                    return;
                }

            }
        }


        /*
         generateCertificate() debe setear los campos state y certificatePath antes
         de insertar el certificado en la BD */
        QString err;
        if (!c.generateCertificate(err))  {
            output.add("certificate", err);
            break;
        }

        success = CertificateMapper().insert(c);
        if (!success)
            output.add("certificate", "InsertError");
        break;
    }

    output.add("success", success);
}

void CertificateResponse::deleteCertificate(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteCertificate");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "CERTIFICATE_DELETE"))
    {
        Certificate c;

        c.setId(params.value("id", "").toUInt());

        success = CertificateMapper().erase(c);
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

/*void CertificateResponse::updateCertificate(JSONP &output, const QHash <QString, QString> &params)
{

}*/

/* Lo que debería hacer acá es enviar el path del archivo en el servidor para que en
   el cliente se puede downloadear.

   Tengo varios get. Uno para obtener los certificatos hechos.
   Otro para obterner los paths. Pueden ser el mismo? Por qué no. Hablarlo con Guido.
*/

QVariantList serializeCertificates(QList <Certificate> certificates)
{
    QVariantList serializedCertificates;

    foreach(Certificate c, certificates) {
        QVariantHash certificateProperties;

        certificateProperties["id"] = c.getId();
        certificateProperties["protn"] = c.getProtN();
        certificateProperties["numprobeta"] = c.getNumProbeta();
        certificateProperties["state"] = c.getState(),
        certificateProperties["client_id"] = c.getClient().getId();
        certificateProperties["date"] = c.getDate();

        /* Este serialize es para el mostrarle los certificados hechos al cliente,
           para qué enviar las siguientes propiedades?
        */
        //certificateProperties["description"] = c.getDescription();
        //certificateProperties["observations"] = c.getObservations();
        //certificateProperties["termicopath"] = c.getTermicoPath();

        certificateProperties["ordencompra"] = c.getOrdenCompra();
        certificateProperties["material_id"] = c.getMaterial().getId();
        certificateProperties["performer_id"] = c.getPerformer().getId();
        certificateProperties["approver_id"] = c.getApprover().getId();
        certificateProperties["reviewer_id"] = c.getReviewer().getId();

        certificateProperties["chemicalanalysis"] = c.getChemicalAnalysis().print();
        certificateProperties["mechanicalanalysis"] = c.getMechanicalAnalysis().print();

        certificateProperties["certificatepath"] = c.getCertificatePath();

        serializedCertificates << certificateProperties;
    }

    return serializedCertificates;
}

void CertificateResponse::getCertificate(JSONP &output, const QHash <QString, QString> &params)
{
    output.add("method", "DeleteCertificate");

    QString email = params.value("email", "").toUtf8();
    QString password = params.value("password", "").toUtf8();

    bool success = false;

    if (hasPermission(email, password, "CERTIFICATE_LIST"))
    {
        QList <Certificate> certificates;
        if (params.keys().contains("id"))
            certificates = CertificateMapper().get(params.value("id").toUInt());
        else
            certificates = CertificateMapper().get();

        success = true;
        output.add("certificates", serializeCertificates(certificates));
    } else
        output.add("permissions", "denied");

    output.add("success", success);
}

void CertificateResponse::generate(QString method, JSONP &output, const QHash <QString, QString> &params)
{
    void (*f) (JSONP &, const QHash <QString, QString> &) = methodTable.value(method, 0);

    if (f != 0)
        return (*f)(output, params);
}
