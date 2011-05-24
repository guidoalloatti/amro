#include "certificateprinter.h"

#include <QPrinter>
#include <QDebug>
#include <QDir>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QWebElement>
#include <QString>

#include <QDir>

#include "certificategenerator.h"

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
}

void CertificatePrinter::print(bool ok)
{
    qDebug() << "En printer " << ok;

    if (!ok) {
        emit requestDone(false);
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    QString certId = view->page()->mainFrame()->findFirstElement("#protn").toPlainText();
    QString path = view->page()->mainFrame()->baseUrl().toLocalFile() + certId + ".pdf";
    printer.setOutputFileName(path);

    view->print(&printer);
    view->hide();
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

    qDebug() << s;

    return s;
}

void CertificatePrinter::generate(Certificate c)
{
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

    QString str = QDir::currentPath();
    //qDebug() << "file://" + str + "/files/";
    QUrl url("file://" + str + "/files/");
    view->setHtml(html, url);

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
                label.setPlainText("Normalizado");
            else
                label.setPlainText("Fallo");

        } else if (label.attribute("id") == "fecha")
            label.setPlainText(c.getDate().toString("dd/MM/yyyy"));
        else if (label.attribute("id") == "realizo")
            label.setPlainText(c.getPerformer().getName() + " " + c.getPerformer().getSurname());
        else if (label.attribute("id") == "aprobo")
            label.setPlainText(c.getApprover().getName() + " " + c.getApprover().getSurname());
        else if (label.attribute("id") == "reviso")
            label.setPlainText(c.getReviewer().getName() + " " + c.getReviewer().getSurname());
    }

    foreach(QWebElement image, allImages) {
        if (image.attribute("id") == "ttimage")
            image.setAttribute("src", c.getTermicoPath());
        else if (image.attribute("id") == "realizo_image")
            image.setAttribute("src", c.getPerformer().getSignature());
        else if (image.attribute("id") == "aprobo_image")
            image.setAttribute("src", c.getApprover().getSignature());
        else if (image.attribute("id") == "reviso_image")
            image.setAttribute("src", c.getReviewer().getSignature());

    }

    QFile newFile("files/" + c.getProtN() + ".html");
    newFile.open(QFile::WriteOnly | QFile::Truncate);

    QTextStream out(&newFile);
    out.setCodec("iso-8859-1");
    out << main->toHtml();
    out.flush();
    newFile.close();

    c.setCertificatePath("files/" + c.getProtN() + ".pdf");

    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(print(bool)));

    //view->load("files/" + c.getProtN() + ".html");

}

