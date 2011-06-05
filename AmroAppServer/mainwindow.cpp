#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QApplication>
#include <QTextCodec>
#include <QDir>
#include <QThreadPool>
#include <QMessageBox>

#include "../DataLibrary/certificate.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(linuxCodec);
    QTextCodec::setCodecForCStrings(linuxCodec);
    QTextCodec::setCodecForLocale(linuxCodec);

    qRegisterMetaType<Certificate>("Certificate");
    printer = CertificatePrinter::getPrinter();

    ui->startButton->setEnabled(false);

    this->currentRequests = 0;

    listener = new RequestListener();
    connect(this, SIGNAL(stopListen()), listener, SLOT(serverStop()));
    connect(this, SIGNAL(startListen()), listener, SLOT(serverStart()));
    connect(listener, SIGNAL(failedListen()), this, SLOT(listenFailed()));
    connect(listener, SIGNAL(requestAccepted()), this, SLOT(newRequest()));
    connect(listener, SIGNAL(finishedRequest()), this, SLOT(requestFinished()));
    connect(this, SIGNAL(cleanRequesters()), listener, SLOT(prepareToExit()));
    connect(listener, SIGNAL(listenerFinished()), this, SLOT(requestersFreed()));
    listener->start();
}

MainWindow::~MainWindow()
{
    delete listener;
    delete printer;
    delete ui;
}

void MainWindow::newRequest()
{
    currentRequests++;
    ui->statusbar->clearMessage();
    ui->statusbar->showMessage("Pedidos actualmente servidos " + QString::number(currentRequests));
}

void MainWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false);
    emit this->startListen();
    ui->stopButton->setEnabled(true);
}

void MainWindow::listenFailed()
{
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    QMessageBox box;
    box.setText("No se pudo conectar al puerto 8080.\nLibere el puerto o intente más tarde.");
    box.exec();
}

void MainWindow::requestFinished()
{
    currentRequests--;
    ui->statusbar->clearMessage();
    ui->statusbar->showMessage("Pedidos actualmente servidos " + QString::number(currentRequests));
}

void MainWindow::on_stopButton_clicked()
{
    ui->stopButton->setEnabled(false);
    emit this->stopListen();
    ui->startButton->setEnabled(true);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   QMessageBox box;
   box.setText("La aplicación se minimizará en la barra de tareas.\nPara terminar la aplicación cliquee el botón Salir.");
   box.exec();
   event->ignore();
   this->showMinimized();
}


void MainWindow::on_quitButton_clicked()
{
    int ret = QMessageBox::Yes;

    if (currentRequests != 0)
        ret = QMessageBox::warning(this, "Salir del Servidor",
                                   "La aplicación está ejecutando " + QString::number(currentRequests) +
                                      " pedidos.\nEstá seguro que desea cerrar el servidor?",
                                   QMessageBox::Yes | QMessageBox::No);
    else
        ret = QMessageBox::warning(this, "Salir del Servidor",
                                   "Está seguro que desea cerrar el servidor?",
                                   QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes)
        emit this->cleanRequesters();
}

void MainWindow::requestersFreed()
{
    QApplication::quit();
}
