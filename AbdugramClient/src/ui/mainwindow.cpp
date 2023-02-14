#include "mainwindow.h"
#include "stackedwidget.h"
#include "hellopage.h"
#include "registrationpage.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setupUi();

    connect(helloPage_, &HelloPage::startMessagingClicked,
            this, [this]() {stackedWidget_->toIndex(1);});

    connect(registrationPage_, &RegistrationPage::backButtonClicked,
            this, [this]() {stackedWidget_->toIndex(0);});
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

    resize(1280, 720);
}
