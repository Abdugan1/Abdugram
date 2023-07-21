#include "application.h"
#include "settings.h"

#include "ui/mainwindow.h"
#include "ui/colorrepository.h"

#include "net/networkhandler.h"

#include <logger/logger.h>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QFontDatabase>
#include <QSettings>
#include <QDebug>

Application::Application(int &argc, char **argv)
    : QApplication{argc, argv}
{
    Logger::init();
    Logger::setEchoMode(true);

    setupFont();
    setupStyleSheet(":/qss/style.qss");
    setupSettings();

    mainWindow_ = std::unique_ptr<MainWindow>(new MainWindow);

    networkHandler()->connectToServer();
}

void Application::saveLoginDataOnSuccess(bool success)
{
    if (success) {
        QSettings settings;
        settings.setValue(settings::net::Username, networkHandler()->lastUsername());
        settings.setValue(settings::net::Password, networkHandler()->lastPassword());
    }
}

void Application::removeLoginData()
{
    QSettings settings;
    settings.setValue(settings::net::Username, "");
    settings.setValue(settings::net::Password, "");
}

void Application::setupStyleSheet(const QString &qssFileName)
{
    QFile qssFile(qssFileName);
    if (!qssFile.open(QFile::ReadOnly)) {
        qDebug() << "Could not read file";
        return;
    }
    QString rawStyleSheet = qssFile.readAll();

    for (auto it = Colors.begin(); it != Colors.end(); ++it) {
        rawStyleSheet.replace('@' + it.key(), it.value().name());
    }

    setStyleSheet(rawStyleSheet);
}

void Application::setupFont()
{
    QFontDatabase::addApplicationFont(":/fonts/Montserrat-Regular.ttf");
    QFontDatabase db;
    setFont(QFont{"Montserrat", 12, QFont::Medium});
}

void Application::setupSettings()
{
    setOrganizationName("Abdu Softwares");
    setOrganizationDomain("abdu.kz");
    setApplicationName("Abdugram");

    connect(networkHandler(), &NetworkHandler::loginResult, this, &Application::saveLoginDataOnSuccess);
    connect(networkHandler(), &NetworkHandler::registerResult, this, &Application::saveLoginDataOnSuccess);
    connect(networkHandler(), &NetworkHandler::loggedOut,   this, &Application::removeLoginData);

}
