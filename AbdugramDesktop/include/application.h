#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QVector>

class QThread;

#include <memory>
#include <functional>

#include "ui/mainwindow.h"

using thread_unique_ptr = std::shared_ptr<QThread>;

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int &argc, char **argv);

private slots:
    void saveLoginDataOnSuccess(bool success);
    void removeLoginData();

private:
    void setupFont();
    void setupSettings();

    void initThreads();
    void initMetaTypes();

    void mainWindowShowLogic();

    void startupLogin();

private:
    std::unique_ptr<MainWindow> mainWindow_;
    QVector<thread_unique_ptr> threads_;
};

#endif // APPLICATION_H
