#include "ui/mainwindow.h"
#include "ui/stackedwidget.h"
#include "ui/hellopage.h"
#include "ui/loginpage.h"
#include "ui/registrationpage.h"
#include "ui/mainpage.h"
#include "ui/problemwidget.h"
#include "sectimer.h"

#include "net/networkhandler.h"

#include <net_common/tcpsession.h>
#include <net_common/consts.h>


#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QDebug>

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
    networkHandler()->connectToServer();
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

void MainWindow::toHelloPage()
{
    stackedWidget_->toWidget(helloPage_);
}

void MainWindow::toLoginPage()
{
    stackedWidget_->toWidget(loginPage_);
}

void MainWindow::toRegistrationPage()
{
    stackedWidget_->toWidget(registrationPage_);
}

void MainWindow::toMainPage()
{
    stackedWidget_->toWidget(mainPage_);
}

void MainWindow::setupUi()
{
    helloPage_ = new HelloPage;

    loginPage_ = new LoginPage;

    registrationPage_ = new RegistrationPage;

    mainPage_ = new MainPage;

    stackedWidget_ = new StackedWidget;
    stackedWidget_->addWidget(helloPage_);
    stackedWidget_->addWidget(loginPage_);
    stackedWidget_->addWidget(registrationPage_);
    stackedWidget_->addWidget(mainPage_);
    stackedWidget_->setCurrentWidget(helloPage_);

    setCentralWidget(stackedWidget_);

    connectionProblem_ = new ProblemWidget{this};
    connectionProblem_->hide();

    resize(1280, 720);
}

void MainWindow::connectUiLogic()
{
    connect(helloPage_, &HelloPage::startMessagingClicked, this, [this]() {
        if (networkHandler()->isConnected()) {
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
    connect(networkHandler(), &NetworkHandler::connectedSucessfully, this, [this]() {
        connectAttempts_ = 0;
        connectionProblem_->hide();
    });

    connect(networkHandler(), &NetworkHandler::connectionError, this, &MainWindow::onConnectionError);

    reconnectSoonTimer_ = new SecTimer{this};
    reconnectSoonTimer_->setDuration(16);

    connect(reconnectSoonTimer_, &SecTimer::timeout1Sec, this, [this](int remaining) {
        connectionProblem_->setRemainingTime(remaining);
    });

    connect(reconnectSoonTimer_, &SecTimer::fullElapsed, this, &MainWindow::connectToServer);

    connect(connectionProblem_, &ProblemWidget::reconnectNowClicked, this, &MainWindow::connectToServer);

    connect(networkHandler(), &NetworkHandler::loginSuccessfully, this, &MainWindow::toMainPage);

    connect(networkHandler(), &NetworkHandler::registerSuccessfully, this, &MainWindow::toMainPage);
}
