#include "responsemapper.h"
#include "response.h"
#include "responsefactory.h"

#include "../DataLibrary/datalib.h"

#include "jsonp.h"

#include <QtCore>
#include <QHttpResponseHeader>

void ResponseMapper::execute(const QString &method, QTextStream &output, const QHash <QString, QString> &params)
{
    // HACER: corregir esto, es temporal, porque si no muere a veces
    if (method == "") return;

    QHttpResponseHeader response(200, "OK", 1, 1);
    //response.setContentType("application/json");
    response.setContentType("text/javascript");
    // HACER: ver si esta bien esto
    response.setValue("Connection", "close");

    output << response.toString();
    output.flush();

    JSONP jsonp(&output, params["callback"]);

    qDebug() << method;

    // HACER: usar new y delete para este caso obvio
    QScopedPointer <Response> r;

    /*
     Qué métodos puede invocar el cliente?

     Ingresar un nuevo cliente --> NewClient
     Borrar un cliente ---> DeleteClient
     Modificar un cierto client ---> UpdateClient (acá tratar con casos especiales como el cambio de número de probeta)
     Recuperar un client ---> GetClient (depende parámetros, lo que devuelve)

     Ingresar un nuevo usuario ---> NewUser
     Borrar un usuario ---> DeleteUser
     Modificar un cierto usuario ---> UpdateUser
     Recuperar cierto usuario ---> GetUser (depende parámetros, lo que devuelve, además debe tener privilegios)
     Login ---> Login

     Ingresar un nuevo material ---> NewMaterial
     Borrar un material ---> DeleteMaterial
     Modificar un cierto material ---> UpdateMaterial
     Recuperar un material ---> GetMaterial (depende parámetros,lo que devuelve)

     Generar un nuevo certificado ---> GenCertificate
     Borrar un certificado ---> DeleteCertificate
     Modificar un cierto certificado ---> UpdateCertificate
     Recuperar cierto certificado ---> GetCertificates (depende parámetros, lo que devuelve)

     Lo que podemos hacer es un ResponseFactory por tipo. O sea, tenemos un objeto respuesta por cliente,
     certificado, etc. En "type" vamos a devolver el tipo y en "method" el método a ejecutar. La fábrica
     va a crear una instancia del tipo a ejecutar.
     */

    r.reset(ResponseFactory().createResponse(params["target"]));

    /*if (target == "User")
        r.reset(new UserResponse(method));
    else if (target == "Client")
        r.reset(new ClientResponse(method));
    else if (target == "Material")
        r.reset(new MaterialResponse(method));
    else if (target == "Certificate")
        r.reset(new CertificateResponse(method));
    else
        qDebug() << "ERROR: method (" << params["method"] << ") not found." << endl;*/

    if (!r.isNull())
        r->generate(params["method"], jsonp, params);
    else
        qDebug() << "ERROR: method (" << params["method"] << ") not found." << endl;

    jsonp.close();
}
