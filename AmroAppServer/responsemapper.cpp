#include "responsemapper.h"
#include "response.h"
#include "responsefactory.h"

#include "../DataLibrary/datalib.h"

#include "jsonp.h"

#include <QtCore>
#include <QHttpResponseHeader>

void ResponseMapper::execute(const QString &method, QTextStream &output, const QHash <QString, QString> &params)
{
    if (method == "") return;

    QHttpResponseHeader response(200, "OK", 1, 1);
    //response.setContentType("application/json");
    response.setContentType("text/javascript");
    // HACER: ver si esta bien esto
    response.setValue("Connection", "close");

    output << response.toString();
    output.flush();

    QByteArray result;
    QTextStream out(&result);

    //JSONP jsonp(&output, params["callback"]);
    JSONP jsonp(&out, params["callback"]);


    qDebug() << method;
    qDebug() << params;

    // HACER: usar new y delete para este caso obvio
    QScopedPointer <Response> r;

    r.reset(ResponseFactory().createResponse(params["target"]));

    if (!r.isNull())
        r->generate(params["method"], jsonp, params);
    else
        qDebug() << "ERROR: method (" << params["method"] << ") not found." << endl;

    jsonp.close();

    qDebug() << "Termine la llamada " << method << " con status: " << result.contains("true");
    output << result;
}
