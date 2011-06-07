/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jun 7 11:13:16 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *statusEdit;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *quitButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(621, 393);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        statusEdit = new QTextEdit(centralwidget);
        statusEdit->setObjectName(QString::fromUtf8("statusEdit"));
        statusEdit->setGeometry(QRect(20, 70, 581, 271));
        statusEdit->setReadOnly(true);
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(20, 10, 151, 51));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        startButton->setFont(font);
        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(450, 10, 151, 51));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setStyleStrategy(QFont::PreferDefault);
        stopButton->setFont(font1);
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));
        quitButton->setGeometry(QRect(520, 350, 82, 22));
        quitButton->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Amro Application Server", 0, QApplication::UnicodeUTF8));
        statusEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Droid Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">Instrucciones de Ejecuci\303\263n:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-siz"
                        "e:10pt;\">1.- Al ejecutar el programa </span><span style=\" font-size:10pt; font-weight:600;\">Amro Appl</span><span style=\" font-size:10pt; font-weight:600;\">ication Server</span><span style=\" font-size:10pt;\">, el servidor se iniciar\303\241 autom\303\241ticamente.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">2.- Presione el bot\303\263n </span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">Det</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">ener Serv</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">i</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">dor</span><span style=\" font-size:10pt;\"> si desea detener el programa sin salir.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" fon"
                        "t-size:10pt;\">3.- Presione el bot\303\263n </span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">Iniciar </span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">Servidor</span><span style=\" font-size:10pt;\"> si desea que el servidor vuelva a escuchar peticiones externas.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">4.- Una vez comenzado el proceso abra la siguiente direcci\303\263n en un navegador preferido:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">http://localhost/</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; "
                        "margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">5.- Si se encuentra en una m\303\241quina diferente a la del servidor, entonces deber\303\241 ingresar la direcci\303\263n IP del equipo en donde reside este \303\272ltimo. Ej:</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\"><br />http://192.168.2.1/</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-in"
                        "dent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">Notas de Uso:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\"><br />1.- Utilizar como navegador por defecto Google Chrome el cual viene incluido en el CD de instalaci\303\263n.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">2.- Para poder subir archivos al servidor (firmas, CSVs, Tratamientos T\303\251rmicos, etc) debe permitir que se ejecute el &quot;popup&quot; cuando sea</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">advertido por su navegador. Le desplegar\303\241 esta opci\303\263n en la parte superior de la p\303\241gina.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; marg"
                        "in-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">3.- A la hora de subir archivos con </span><span style=\" font-size:10pt; font-weight:600;\">Ordenes de Compra </span><span style=\" font-size:10pt;\">debe respetar el siguiente formato de archivo:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">	</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    * El archivo debe ser originalmente o transformado a CSV.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    * El formato del CSV debe tener como caracter de separaci\303\263n entre columnas el  ; (punto y coma) y no debe tener ning\303\272n caracter</span><"
                        "/p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">       para encerrar al valor de cada celda. </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    * El encabezado (primera fila) del CSV debe contener valores tales que el servidor permita reconocer de qu\303\251 columna se trata. Para</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">       esto debe contener s\303\255 o s\303\255 las palabras clave: </span><span style=\" font-size:10pt; font-weight:600;\">colada</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">compra</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">ma"
                        "terial</span><span style=\" font-size:10pt;\">,</span><span style=\" font-size:10pt; font-weight:600;\"> cliente</span><span style=\" font-size:10pt;\"> y </span><span style=\" font-size:10pt; font-weight:600;\">descrip</span><span style=\" font-size:10pt;\">.  </span><span style=\" font-size:10pt; font-style:italic;\">cliente</span><span style=\" font-size:10pt;\"> es el \303\272nico campo no obligatorio.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">       No importa si est\303\241n en min\303\272scula o </span><span style=\" font-size:10pt;\">may\303\272scula o si est\303\241n en conjunto con otras palabras. Ej: N\302\272 de colada.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    * El cliente le mostrar\303\241 la lista de errores obtenidos de la recolecci\303\263"
                        "n de datos del archivo subido.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    * Ejemplo de CSV (cabecera, s\303\263lo una fila). El servidor ignorar\303\241 el valor de O/SIP:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">	</span><span style=\" font-size:10pt; font-style:italic;\">N\302\272 COLADA</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">;</span><span style=\" font-size:10pt; font-style:italic;\">O/COMPRA</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">;</span><span style=\" font-size:10pt; font-style:italic;\">MATERIAL</span><span style="
                        "\" font-size:10pt; font-weight:600; font-style:italic;\">;</span><span style=\" font-size:10pt; font-style:italic;\">O/SIP</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">;</span><span style=\" font-size:10pt; font-style:italic;\">DESCRIPCION</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">	M-566</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">;</span><span style=\" font-size:10pt; font-style:italic;\">7579 TEL</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">;</span><span style=\" font-size:10pt; font-style:italic;\">WCB</span><span style=\" font-size:10pt; font-weight:600; font-style:italic;\">;;</span><span style=\" font-size:10pt; font-style:italic;\">3-CPO E-4&quot;300 RJ</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0p"
                        "x; -qt-block-indent:0; text-indent:0px; font-size:10pt; font-style:italic;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">4.- A la hora de subir archivos de </span><span style=\" font-size:10pt; font-weight:600;\">A</span><span style=\" font-size:10pt; font-weight:600;\">n\303\241lisis </span><span style=\" font-size:10pt; font-weight:600;\">Q</span><span style=\" font-size:10pt; font-weight:600;\">u\303\255micos</span><span style=\" font-size:10pt;\"> se siguen con las misma recomendaciones para archivos con ordenes de compra</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">con la diferencia que las palabras claves requeridas son: </span><span style=\" font-size:10pt; font-weight:600;\">probeta</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; fon"
                        "t-weight:600;\">fe</span><span style=\" font-size:10pt; font-weight:600;\">cha</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">calidad</span><span style=\" font-size:10pt;\"> y las todas las columnas que correspondan al</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">los valores de an\303\241lisis mec\303\241nico </span><span style=\" font-size:10pt; font-weight:600;\">C</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">S</span><span style=\" font-size:10pt; font-weight:600;\">i</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">Mn</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">P</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">S</span><span style=\" "
                        "font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">Cr</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">Ni</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">Mo</span><span style=\" font-size:10pt;\">, </span><span style=\" font-size:10pt; font-weight:600;\">Cu</span><span style=\" font-size:10pt;\"> y </span><span style=\" font-size:10pt; font-weight:600;\">V</span><span style=\" font-size:10pt;\">. Ej:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">	</span><span style=\" font-size:10pt; font-style:italic;\">Probeta;ID-3;ID-4;Fecha;Colada N\302\272;Calidad;Cantidad PF/ Detalle;Cantidad Aros / Detalle;C;"
                        "Si;Mn;P;S;Cr;Ni;Mo;Cu;V</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-style:italic;\">	</span><span style=\" font-size:10pt; font-style:italic;\">AR 1098;;CRIS;21/07/2010;891 F H1;WCB;CUNA E2-300/600-F;;0,207;0,315;0,94;0,024;0,009;0,123;0,035;0,015;0,014;0,003</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Iniciar el Servidor", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("MainWindow", "Detener el Servidor", 0, QApplication::UnicodeUTF8));
        quitButton->setText(QApplication::translate("MainWindow", "Salir", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
