#include "mainwindow.h"
#include "stackedwidget.h"
#include "hellopage.h"
#include "loginpage.h"
#include "registrationpage.h"
#include "problemwidget.h"
#include "../sectimer.h"

#include <api_client/tcpsession.h>
#include <api_client/consts.h>
#include <QLabel>
#include <QMovie>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setupUi();

    connectUiLogic();
    connectTcpLogic();

    connectToServer();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    connectionProblem_->move(10, height() - 20 - connectionProblem_->height());
}

void MainWindow::connectToServer()
{
    reconnectSoonTimer_->stop();
    tcpSession_->connectToHost(consts::server::Address, consts::server::Port);
}

void MainWindow::onConnectionError()
{
    if (connectAttempts_++ < 6) {
        connectionProblem_->setTextToConnecting();
        QTimer::singleShot(500, this, &MainWindow::connectToServer);
    } else {
        connectAttempts_ = 0;
        reconnectSoonTimer_->start();
    }
    connectionProblem_->setVisible(true);
}

void MainWindow::setupUi()
{
    helloPage_ = new HelloPage;

    loginPage_ = new LoginPage;

    registrationPage_ = new RegistrationPage;

    stackedWidget_ = new StackedWidget;
    stackedWidget_->addWidget(helloPage_);
    stackedWidget_->addWidget(loginPage_);
    stackedWidget_->addWidget(registrationPage_);
    stackedWidget_->setCurrentWidget(helloPage_);

    setCentralWidget(stackedWidget_);

    connectionProblem_ = new ProblemWidget{this};
    connectionProblem_->hide();

    resize(1280, 720);
}

void MainWindow::connectUiLogic()
{
    connect(helloPage_, &HelloPage::startMessagingClicked, this, [this]() {
        if (tcpSession_->state() == QTcpSocket::ConnectedState) {
            stackedWidget_->toWidget(loginPage_);
        }
    });

    connect(loginPage_, &LoginPage::backButtonClicked, this, [this]() {
        stackedWidget_->toWidget(helloPage_);
    });

    connect(loginPage_, &LoginPage::toRegisterPageClicked, this, [this]() {
        stackedWidget_->toWidget(registrationPage_);
    });

    connect(registrationPage_, &RegistrationPage::backButtonClicked, this, [this]() {
        stackedWidget_->toWidget(helloPage_);
    });

    connect(registrationPage_, &RegistrationPage::toLoginPageClicked, this, [this]() {
        stackedWidget_->toWidget(loginPage_);
    });
}

void MainWindow::connectTcpLogic()
{
    tcpSession_ = new TcpSession;

    connect(tcpSession_, &TcpSession::connected, this, [this]() {
        connectAttempts_ = 0;
        connectionProblem_->hide();
    });

    connect(tcpSession_, &TcpSession::errorOccurred, this, &MainWindow::onConnectionError);

    reconnectSoonTimer_ = new SecTimer{this};
    reconnectSoonTimer_->setDuration(16);

    connect(reconnectSoonTimer_, &SecTimer::timeout1Sec, this, [this](int remaining) {
        connectionProblem_->setRemainingTime(remaining);
    });

    connect(reconnectSoonTimer_, &SecTimer::fullElapsed, this, &MainWindow::connectToServer);

    connect(connectionProblem_, &ProblemWidget::reconnectNowClicked, this, &MainWindow::connectToServer);

    connect(registrationPage_, &RegistrationPage::registerRequested, [this](const AbduMessagePtr &registerMessage) {
        tcpSession_->send(registerMessage);
    });
}
