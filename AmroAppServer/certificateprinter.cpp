#include "certificateprinter.h"

#include <QPrinter>
#include <QDebug>
#include <QDir>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QWebElement>
#include <QString>
#include <QLocale>
#include <QRegExp>

#include "certificategenerator.h"

static QString client_path = "../AmroClient/certificados/";
bool canPrint = false;

CertificatePrinter* CertificatePrinter::pinstance = 0;

CertificatePrinter* CertificatePrinter::getPrinter()
{
    if (pinstance == NULL) {
        pinstance  = new CertificatePrinter;
    }

    return pinstance;
}


CertificatePrinter::CertificatePrinter()
{
    view = new QWebView;
    dir.cd(client_path);
}

/*
 Termino andando, no sé por qué. Problemas con la sincro
 entre la señal de carga de nueva página y el método
 print.
 */

void CertificatePrinter::print(bool ok)
{
    qDebug() << "En printer" << ok;

    /*if (!canPrint) {
        qDebug() << "No puede imprimir";
        return;
    }*/

    canPrint = false;
    if (!ok) {
        emit requestDone(false);
        qDebug() << "Fallos request";
        return;
    }

    disconnect(view, SIGNAL(loadFinished(bool)), this, SLOT(print(bool)));

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    //QString certId = view->page()->mainFrame()->findFirstElement("#protn").toPlainText();
    //QString path = view->page()->mainFrame()->baseUrl().toLocalFile() + certId + ".pdf";
    //QString path = client_path + certId + ".pdf";
    QString path = client_path + current.getProtN() + ".pdf";
    //qDebug() << path;
    //Q_ASSERT(!certId.isEmpty());
    printer.setOutputFileName(path);

    view->print(&printer);
    view->close();
    view->deleteLater();
    this->mutex.unlock();
    emit requestDone(true);
}

QWebView* CertificatePrinter::CertificatePrinter::getView()
{
    return this->view;
}


static QString toString(double d)
{
    QString s;

    s.sprintf("%.2f", d);

    //qDebug() << s;

    return s;
}


void CertificatePrinter::generate(Certificate c)
{
    this->mutex.lock();
    current = c;

    QFile htmlTemplate("files/template.html");

    if (!htmlTemplate.open(QFile::ReadOnly)) {
        qDebug() << "No se pudo abrir el template html";
        emit requestDone(false);
        return;
    }

    QByteArray content = htmlTemplate.readAll();

    if (content.isEmpty()) {
        qDebug() << "No se pudo leer el contenido del template html";
        htmlTemplate.close();
        emit requestDone(false);
        return;
    }

    QString html(content);

    htmlTemplate.close();

    //view->close();
    this->view = new QWebView;

    QString pwd = dir.path();
    //qDebug() << "file://" + str + "/files/";
    //QUrl url("file:///home/pmata/amro/AmroClientServer/AmroClient/certificados/");
    //QUrl url(client_path);
    //QUrl url("file://" + pwd + "/");
    //qDebug() << url;
    view->setHtml(html,  QUrl::fromLocalFile(pwd + "/"));

    //view->setHtml(html, url);

    QWebFrame *main = view->page()->mainFrame();

    QWebElementCollection labels = main->findAllElements("label");
    QList <QWebElement> allLabels = labels.toList();

    QWebElementCollection images = main->findAllElements("img");
    QList <QWebElement> allImages = images.toList();

    foreach(QWebElement label, allLabels) {
        if (label.attribute("id") == "cliente")
            label.setPlainText(c.getClient().getName());
        else if (label.attribute("id") == "material")
            label.setPlainText(c.getMaterial().getName());
        else if (label.attribute("id") == "descripcion")
            label.setPlainText(c.getDescription());
        else if (label.attribute("id") == "oc")
            label.setPlainText(c.getOrdenCompra());
        else if (label.attribute("id") == "protn")
            label.setPlainText(c.getProtN());
        else if (label.attribute("id") == "identificacion")
            label.setPlainText(c.getNumProbeta());
        else if (label.attribute("id") == "c")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("c")));
        else if (label.attribute("id") == "mn")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("mn")));
        else if (label.attribute("id") == "si")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("si")));
        else if (label.attribute("id") == "p")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("p")));
        else if (label.attribute("id") == "s")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("s")));
        else if (label.attribute("id") == "cr")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("cr")));
        else if (label.attribute("id") == "ni")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("ni")));
        else if (label.attribute("id") == "mo")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("mo")));
        else if (label.attribute("id") == "cu")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("cu")));
        else if (label.attribute("id") == "v")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("v")));
        else if (label.attribute("id") == "ce")
            label.setPlainText(toString(c.getChemicalAnalysis().getMaxValue("ce")));
        else if (label.attribute("id") == "tension")
            label.setPlainText(toString(c.getMechanicalAnalysis().getMaxValue("tension_rotura")));
        else if (label.attribute("id") == "fluencia")
            label.setPlainText(toString(c.getMechanicalAnalysis().getMaxValue("limite_fluencia")));
        else if (label.attribute("id") == "alargamiento")
            label.setPlainText(toString(c.getMechanicalAnalysis().getMaxValue("alargamiento")));
        else if (label.attribute("id") == "estriccion")
            label.setPlainText(toString(c.getMechanicalAnalysis().getMaxValue("estriccion")));
        else if (label.attribute("id") == "resiliencia")
            label.setPlainText(toString(c.getMechanicalAnalysis().getMaxValue("resiliencia")));
        else if (label.attribute("id") == "dureza")
            label.setPlainText(toString(c.getMechanicalAnalysis().getMaxValue("dureza")));
        else if (label.attribute("id") == "observaciones")
            label.setPlainText(c.getObservations());
        else if (label.attribute("id") == "termico") {
            if (c.getState() == PASSED)
                label.setPlainText(c.getTermicalTreatment().getDate().toString("dd/MM/yyyy") + "--> Normalizado");
            else
                label.setPlainText(c.getTermicalTreatment().getDate().toString("dd/MM/yyyy") + "--> Falló");

        } else if (label.attribute("id") == "fecha")
            label.setPlainText(c.getDate().toString("dd/MM/yyyy"));
        else if (label.attribute("id") == "realizo")
            label.setPlainText(c.getPerformer().getName() + " " + c.getPerformer().getSurname());
        else if (label.attribute("id") == "aprobo")
            label.setPlainText(c.getApprover().getName() + " " + c.getApprover().getSurname());
        else if (label.attribute("id") == "reviso")
            label.setPlainText(c.getReviewer().getName() + " " + c.getReviewer().getSurname());
    }


    int certificatePathLength = QString("certificados/").length();

    qDebug() << "asdfasdfsadfasdfasdf";

    QString tt_image = c.getTermicalTreatment().getImagePath().mid(certificatePathLength);

    QString performer_image = c.getPerformer().getSignature().mid(certificatePathLength);

    QString reviewer_image = c.getReviewer().getSignature().mid(certificatePathLength);

    QString approver_image = c.getApprover().getSignature().mid(certificatePathLength);


    foreach(QWebElement image, allImages) {
        if (image.attribute("id") == "ttimage")
            //image.setAttribute("src", c.getTermicoPath());
            image.setAttribute("src", tt_image);
        else if (image.attribute("id") == "realizo_image")
            image.setAttribute("src", performer_image);
        else if (image.attribute("id") == "aprobo_image")
            image.setAttribute("src", approver_image);
        else if (image.attribute("id") == "reviso_image")
            image.setAttribute("src", reviewer_image);

    }

    QFile newFile(client_path + c.getProtN() + ".html");
    newFile.open(QFile::WriteOnly | QFile::Truncate);

    QTextStream out(&newFile);
    out.setCodec("iso-8859-1");
    out << main->toHtml();
    out.flush();
    newFile.close();

    c.setCertificatePath("certificados/" + c.getProtN() + ".pdf");



    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(print(bool)));
    canPrint = true;
    //qDebug() << QUrl::fromLocalFile(pwd + "/" + c.getProtN() + ".html");
    view->load(QUrl::fromLocalFile(pwd + "/" + c.getProtN() + ".html"));
    //view->reload();
    //view->show();

}

