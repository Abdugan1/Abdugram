#include "application.h"
#include "settings.h"

#include "ui/mainwindow.h"

#include "net/networkhandler.h"

#include <logger/logger.h>

#include <sql_client/data_structures/chatitem.h>
#include <sql_client/databaseclient.h>

#include <net_common/messages/abdumessage.h>

#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>
#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/messagereads.h>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QFontDatabase>
#include <QSettings>
#include <QThread>
#include <QDebug>

void deleteThread(QThread *thread)
{
    thread->quit();
    thread->wait();
}

thread_unique_ptr createThread(QObject *parent)
{
    auto thread = thread_unique_ptr(new QThread{parent}, deleteThread);
    thread->start();
    return thread;
}

Application::Application(int &argc, char **argv)
    : app_{argc, argv}
{
    initMetaTypes();
    initThreads();
    Logger::init();
    Logger::setEchoMode(true);

    setupFont();
    setupSettings();

    mainWindow_ = std::unique_ptr<MainWindow>(new MainWindow);
    mainWindowShowLogic();

    networkHandler()->connectToServer();
}

int Application::exec()
{
    return app_.exec();
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

void Application::setupFont()
{
    QFontDatabase::addApplicationFont(":/fonts/Montserrat-Regular.ttf");
    app_.setFont(QFont{"Montserrat", 11, QFont::Medium});
}

void Application::setupSettings()
{
    app_.setOrganizationName("Abdu Softwares");
    app_.setOrganizationDomain("abdu.kz");
    app_.setApplicationName("Abdugram");

    connect(networkHandler(), &NetworkHandler::loginResult, this, &Application::saveLoginDataOnSuccess);
    connect(networkHandler(), &NetworkHandler::registerResult, this, &Application::saveLoginDataOnSuccess);

    connect(networkHandler(), &NetworkHandler::loggedOut,   this, &Application::removeLoginData);
}

void Application::initThreads()
{
    const int size = QThread::idealThreadCount();
    if (size > 0) {
        threads_.append(createThread(this));
        networkHandler()->moveToThread(threads_.last().get());
        database()->moveToThread(threads_.last().get());
    }
}

void Application::initMetaTypes()
{
    qRegisterMetaType<AbduMessagePtr>("AbduMessagePtr");
    qRegisterMetaType<AbduMessage>("AbduMessage");

    qRegisterMetaType<Chat>("Chat");
    qRegisterMetaType<ChatUser>("ChatUser");
    qRegisterMetaType<Message>("Message");
    qRegisterMetaType<User>("User");
    qRegisterMetaType<QList<User>>();
    qRegisterMetaType<MessageRead>("MessageRead");
    qRegisterMetaType<QList<MessageRead>>("");

    qRegisterMetaType<ChatViewItem>("ChatViewItem");
    qRegisterMetaType<QList<ChatViewItem>>();
}

void Application::mainWindowShowLogic()
{
    const QSettings settings;
    const bool hasLoginData = !(settings.value(settings::net::Username).toString().isEmpty()
                               && settings.value(settings::net::Password).toString().isEmpty());
    if (!hasLoginData) {
        mainWindow_->toHelloPage();
        mainWindow_->show();
    } else {
        mainWindow_->toMainPage();

        connect(networkHandler(), &NetworkHandler::connectedSucessfully, this, &Application::startupLogin);

        auto mwConn = std::make_shared<QMetaObject::Connection>();
        *mwConn = connect(mainWindow_.get(), &MainWindow::pageSlideFinished, this, [this, mwConn]() {
            mainWindow_->show();
            disconnect(*mwConn);
        });
    }
}

void Application::startupLogin()
{
    disconnect(networkHandler(), &NetworkHandler::connectedSucessfully, this, &Application::startupLogin);

    const QSettings settings;
    const auto username = settings.value(settings::net::Username).toString();
    const auto password = settings.value(settings::net::Password).toString();

    networkHandler()->sendLoginRequest(username, password);
}
