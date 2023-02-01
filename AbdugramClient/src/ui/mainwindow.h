#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class StackedWidget;
class HelloPage;
class RegistrationPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

private:
    void setupUi();

private:
    StackedWidget    *stackedWidget_ = nullptr;

    HelloPage        *helloPage_ = nullptr;
    RegistrationPage *registrationPage_ = nullptr;

};

#endif // MAINWINDOW_H
