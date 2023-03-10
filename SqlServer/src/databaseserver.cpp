#include "databaseserver.h"

#include <QDir>
#include <QDirIterator>
#include <QSqlError>
#include <QDebug>

const QString HostName = "localhost";
const QString DbName   = "abdugram";
const QString UserName = "abdu";
const QString Password = "AbduganiYerzhanov002@!";

DatabaseServer *DatabaseServer::instance()
{
    static DatabaseServer *self = new DatabaseServer;
    return self;
}

void DatabaseServer::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(HostName);
    db.setDatabaseName(DbName);
    db.setUserName(UserName);
    db.setPassword(Password);

    if (db.open())
        createTables();
    else
        qFatal(qPrintable("Couldn't open database!" + db.lastError().text()));
}

void DatabaseServer::createTables()
{
    const QString rootPath("./.sql");
    executeAllSqlFilesInRootDir(rootPath, "create.sql");
    executeAllSqlFilesInRootDir(rootPath, "constraints.sql");
}
