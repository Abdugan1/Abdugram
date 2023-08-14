#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <net_common/messages/abdumessage.h>

class StackedWidget;
class HelloPage;
class LoginPage;
class RegistrationPage;
class ProblemWidget;
class MainPage;

class SideMenu;

class TcpSession;
class ClientMessageVisitor;

class SecTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void pageSlideFinished();

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void toHelloPage();
    void toLoginPage();
    void toRegistrationPage();
    void toMainPage();

private slots:
    void connectToServer();

    void onConnected();
    void onConnectionError();

    void onLoginResult(bool success);
    void onRegisterResult(bool success);

    void bringToFront();

private:
    void setupUi();

    void connectUiLogic();
    void connectTcpLogic();

private:
    bool startupLogin_ = false;

    int connectAttempts_ = 0;
    SecTimer *reconnectSoonTimer_       = nullptr;
    ProblemWidget *connectionProblem_   = nullptr;

    StackedWidget    *stackedWidget_ = nullptr;

    HelloPage        *helloPage_            = nullptr;
    RegistrationPage *registrationPage_     = nullptr;
    LoginPage        *loginPage_            = nullptr;
    MainPage         *mainPage_             = nullptr;

    friend class ClientMessageVisitor;
};

#endif // MAINWINDOW_H
