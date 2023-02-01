#include <QCoreApplication>
#include <QThreadPool>
#include <QDebug>

#include "serverwindow.h"

#include <api_sql_server/database.h>
#include <logger/logger.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Logger::init();

    qInfo() << "\n\nApp started";

    Database::connectToDatabase();

    ServerWindow serverWindow;
    serverWindow.run();

    return app.exec();
}
