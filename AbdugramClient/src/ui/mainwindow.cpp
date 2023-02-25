#include "mainwindow.h"
#include "stackedwidget.h"
#include "hellopage.h"
#include "registrationpage.h"
#include "problemwidget.h"
#include "../sectimer.h"

#include <api_client/tcpsession.h>
#include <api_client/consts.h>
#include <QLabel>
#include <QMovie>

const QString ConnectionErrorStr = QObject::tr("Reconnect in %1");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setupUi();

    connect(helloPage_, &HelloPage::startMessagingClicked,
            this, [this]() {stackedWidget_->toIndex(1);});

    connect(registrationPage_, &RegistrationPage::backButtonClicked,
            this, [this]() {stackedWidget_->toIndex(0);});


    //
    tcpSession_ = new TcpSession;

    connect(tcpSession_, &TcpSession::connected, this, [this]() {
        connectionProblem_->hide();
    });

    connect(tcpSession_, &TcpSession::errorOccurred, this, [this]() {
        connectionProblem_->show();
        reconnectTimer_->start();
    });

    reconnectTimer_ = new SecTimer{this};
    reconnectTimer_->setDuration(15);

    connect(reconnectTimer_, &SecTimer::timeout1Sec, this, [this](int remaining) {
        connectionProblem_->setText(ConnectionErrorStr.arg(QString::number(remaining)));
    });

    connect(reconnectTimer_, &SecTimer::stopped, this, [this]() {
        tcpSession_->connectToHost(consts::server::Address, consts::server::Port);
    });


    tcpSession_->connectToHost(consts::server::Address, consts::server::Port);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    connectionProblem_->move(10, height() - 20 - connectionProblem_->height());
}

void MainWindow::setupUi()
{
    helloPage_ = new HelloPage;

    registrationPage_ = new RegistrationPage;

    stackedWidget_ = new StackedWidget;
    stackedWidget_->addWidget(helloPage_);
    stackedWidget_->addWidget(registrationPage_);
    stackedWidget_->setCurrentWidget(helloPage_);

    setCentralWidget(stackedWidget_);

    connectionProblem_ = new ProblemWidget{this};
    connectionProblem_->setSizeByTemplateText(ConnectionErrorStr.arg("XX"));
    connectionProblem_->hide();

    resize(1280, 720);
}
