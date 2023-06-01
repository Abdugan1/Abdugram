#include "databaseclient.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

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
    QSqlQuery enableForeignKeys{"PRAGMA foreign_keys = ON;"};

    if (!enableForeignKeys.exec()) {
        qFatal(qPrintable("Couldn't enable keys!" + enableForeignKeys.lastError().text()));
    }

    QString fileName("./.sql/create/create.sql");
    QString queries = readFullFile(fileName);

    QStringList queryList = queries.split(";");
    for (QString query : queryList) {
        query = query.trimmed();
        if (query.isEmpty())
            continue;
        QSqlQuery createQuery{query};
        if (!createQuery.exec()) {
            qFatal(qPrintable("Couldn't execute query!" + createQuery.lastError().text()));
        }
    }
}
