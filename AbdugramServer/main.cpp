#include <QCoreApplication>
#include <QThreadPool>
#include <QDebug>

#include "serverwindow.h"

#include <api_server/server.h>
#include <api_sql_server/database.h>
#include <logger/logger.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Logger::init();

    qInfo() << "\n\nApp started";

    Database::connectToDatabase();

    QThread windowThread;
    ServerWindow serverWindow;
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

    windowThread.start();
    serverThread.start();

    return app.exec();
}
