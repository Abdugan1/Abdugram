#include "databaseclient.h"

#include <QSqlError>

const QString DbName = "abdugram";

DatabaseClient *DatabaseClient::instance()
{
    static DatabaseClient *self = new DatabaseClient;
    return self;
}

void DatabaseClient::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(".sql/" + DbName);

    if (db.open())
        createTables();
    else
        qFatal(qPrintable("Couldn't open database!" + db.lastError().text()));
}

void DatabaseClient::createTables()
{
    const QString rootPath("./.sql");
    executeAllSqlFilesInRootDir(rootPath, "create.sql");
}
