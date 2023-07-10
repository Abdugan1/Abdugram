#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QPointer>

class MainWindow;

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

private:
    QPointer<MainWindow> mainWindow_ = nullptr;
};

#endif // APPLICATION_H
