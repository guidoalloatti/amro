#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

#include "certificateprinter.h"
#include "requestlistener.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CertificatePrinter *printer;
    RequestListener *listener;
    quint32 currentRequests;

signals:
    void stopListen();
    void startListen();
    void cleanRequesters();

private slots:
    void on_quitButton_clicked();
    void newRequest();
    void listenFailed();
    void requestFinished();
    void on_stopButton_clicked();
    void on_startButton_clicked();
    void requestersFreed();
};

#endif // MAINWINDOW_H
