#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class StackedWidget;
class HelloPage;
class RegistrationPage;
class ProblemWidget;

class TcpSession;

class SecTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void setupUi();

private:
    TcpSession *tcpSession_ = nullptr;

    SecTimer *reconnectTimer_ = nullptr;
    ProblemWidget *connectionProblem_ = nullptr;

    StackedWidget    *stackedWidget_ = nullptr;

    HelloPage        *helloPage_ = nullptr;
    RegistrationPage *registrationPage_ = nullptr;

};

#endif // MAINWINDOW_H
