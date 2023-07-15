#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <memory>

#include "ui/mainwindow.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int &argc, char **argv);

private slots:
    void saveLoginDataOnSuccess(bool success);
    void removeLoginData();

private:
    void setupStyleSheet(const QString &qssFileName);
    void setupFont();
    void setupSettings();

private:
    std::unique_ptr<MainWindow> mainWindow_;
};

#endif // APPLICATION_H
