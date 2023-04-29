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

class TcpSession;
class ClientMessageVisitor;

class SecTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void connectToServer();
    void onConnectionError();

    void toHelloPage();
    void toLoginPage();
    void toRegistrationPage();
    void toMainPage();

private:
    void setupUi();

    void connectUiLogic();
    void connectTcpLogic();

private:
    int connectAttempts_ = 0;
    SecTimer *reconnectSoonTimer_       = nullptr;
    ProblemWidget *connectionProblem_   = nullptr;

    StackedWidget    *stackedWidget_ = nullptr;

    HelloPage        *helloPage_            = nullptr;
    LoginPage        *loginPage_            = nullptr;
    RegistrationPage *registrationPage_     = nullptr;
    MainPage         *mainPage_             = nullptr;

    friend class ClientMessageVisitor;
};

#endif // MAINWINDOW_H
