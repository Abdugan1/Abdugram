#include <QCoreApplication>
#include <QThreadPool>
#include <QFileSystemWatcher>
#include <QDebug>

#include "serverwindow.h"
#include "serverlogger.h"

#include <api_server/server.h>
#include <api_server/messages/abdumessage.h>

#include <api_sql_server/database.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Logger::init();

    qRegisterMetaType<AbduMessagePtr>("AbduMessagePtr");

    LogFilePtr serverLogFile{new LogFile{"server.log"}};

    ServerLogger::instance().setLogFile(serverLogFile);

    qInfo() << "\n\nApp started";

    Database::connectToDatabase();

    QThread windowThread;
    ServerWindow serverWindow(serverLogFile);
    serverWindow.moveToThread(&windowThread);
    QObject::connect(&windowThread, &QThread::started,
                     &serverWindow, &ServerWindow::run);

    QThread serverThread;
    Server server;
    server.moveToThread(&serverThread);

    // quit window and server threads
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&windowThread, &serverThread]() {
        windowThread.quit();
        serverThread.quit();

        windowThread.wait();
        serverThread.wait();
    });

    //
    QObject::connect(&serverWindow, &ServerWindow::toggleServerRequested,
                     &server,       &Server::toggle);

    QObject::connect(&server, &Server::started, [&serverWindow]() {
        serverWindow.setMainMenuServerStatus(true);
    });

    QObject::connect(&server, &Server::stopped, [&serverWindow]() {
        serverWindow.setMainMenuServerStatus(false);
    });

    //
    QFileSystemWatcher serverLogWatcher;
    serverLogWatcher.addPath(serverLogFile->filePath());

    QObject::connect(&serverLogWatcher, &QFileSystemWatcher::fileChanged, [&](){
        serverWindow.updateLogsView();
    });

    QObject::connect(&server, &Server::logCreated, [](const QString &log) {
        ServerLogger::instance().writeLog(log);
    });

    windowThread.start();
    serverThread.start();

    return app.exec();
}
