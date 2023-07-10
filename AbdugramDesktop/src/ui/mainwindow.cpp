#include "ui/mainwindow.h"
#include "ui/stackedwidget.h"
#include "ui/hellopage.h"
#include "ui/loginpage.h"
#include "ui/registrationpage.h"
#include "ui/mainpage.h"
#include "ui/problemwidget.h"

#include "sectimer.h"
#include "settings.h"

#include "net/networkhandler.h"

#include <net_common/tcpsession.h>
#include <net_common/consts.h>

#include <QSettings>
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

void MainWindow::onConnected()
{
    connectAttempts_ = 0;
    connectionProblem_->hide();

    startupLogin();
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

void MainWindow::onLoginResult(bool success)
{
    if (startupLogin_) {
        onStartupLoginResult(success);
    } else if (!success) {
        // TODO: Show error
        return;
    }
}

void MainWindow::onRegisterResult(bool success)
{
    if (success) {
        toMainPage();
    } else {
        // TODO: Show error
    }
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

void MainWindow::startupLogin()
{
    startupLogin_ = true;

    const QSettings settings;
    const auto username = settings.value(settings::net::Username).toString();
    const auto password = settings.value(settings::net::Password).toString();

    if (username.isEmpty() || password.isEmpty()) {
        show();
        return;
    }

    networkHandler()->sendLoginRequest(username, password);
}

void MainWindow::onStartupLoginResult(bool success)
{
    if (!success) {
        show();
    } else {
        toMainPage();
        connect(stackedWidget_, &StackedWidget::slideFinished, this, &MainWindow::onStartupLoginSuccess);
    }
}

void MainWindow::onStartupLoginSuccess()
{
    disconnect(stackedWidget_, &StackedWidget::slideFinished, this, &MainWindow::onStartupLoginSuccess);
    show();
}

void MainWindow::setupUi()
{
    helloPage_ = new HelloPage;

    registrationPage_ = new RegistrationPage;

    loginPage_ = new LoginPage;

    mainPage_ = new MainPage;

    stackedWidget_ = new StackedWidget;
    stackedWidget_->addWidget(helloPage_);
    stackedWidget_->addWidget(registrationPage_);
    stackedWidget_->addWidget(loginPage_);
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
            toRegistrationPage();
        }
    });

    connect(loginPage_, &LoginPage::backButtonClicked, this, &MainWindow::toHelloPage);

    connect(loginPage_, &LoginPage::toRegisterPageClicked, this, &MainWindow::toRegistrationPage);

    connect(registrationPage_, &RegistrationPage::backButtonClicked, this, &MainWindow::toHelloPage);

    connect(registrationPage_, &RegistrationPage::toLoginPageClicked, this, &MainWindow::toLoginPage);
}

void MainWindow::connectTcpLogic()
{
    connect(networkHandler(), &NetworkHandler::connectedSucessfully, this, &MainWindow::startupLogin);

    connect(networkHandler(), &NetworkHandler::connectionError, this, &MainWindow::onConnectionError);

    connect(connectionProblem_, &ProblemWidget::reconnectNowClicked, this, &MainWindow::connectToServer);

    connect(networkHandler(), &NetworkHandler::loginResult, this, &MainWindow::onLoginResult);

    connect(networkHandler(), &NetworkHandler::registerResult, this, &MainWindow::onRegisterResult);

    connect(networkHandler(), &NetworkHandler::loggedOut, this, &MainWindow::toHelloPage);

    //
    reconnectSoonTimer_ = new SecTimer{this};
    reconnectSoonTimer_->setDuration(16);

    connect(reconnectSoonTimer_, &SecTimer::fullElapsed, this, &MainWindow::connectToServer);

    connect(reconnectSoonTimer_, &SecTimer::timeout1Sec, this, [this](int remaining) {
        connectionProblem_->setRemainingTime(remaining);
    });
}
