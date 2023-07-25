#include "database.h"
#include "databaseclient.h"

#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

const QString DbName = "abdugram";

bool SqlDatabase::tablesWasCreated_ = false;
int  SqlDatabase::databaseId_ = 0;

SqlDatabase::SqlDatabase()
    : QSqlDatabase{addDatabase("QSQLITE", QString::number(databaseId_++))}
{
}

int SqlDatabase::ownId() const
{
    return ownId_;
}

void SqlDatabase::setOwnId(int newOwnId)
{
    ownId_ = newOwnId;
    tablesWasCreated_ = false;
}

void SqlDatabase::connect()
{
    Q_ASSERT(::database()->ownId() != -1);

    if (::database()->ownId() == ownId_)
        return;

    setOwnId(::database()->ownId());

    if (isOpen())
        close();

    setDatabaseName(".sql/" + DbName + "_" + QString::number(ownId_));

    if (!open()) {
        qFatal(qPrintable("Couldn't open database!" + lastError().text()));
    }
    if (!tablesWasCreated_) {
        createTables();
    }
}

void SqlDatabase::createTables()
{
    QSqlQuery enableForeignKeys{"PRAGMA foreign_keys = ON;", *this};

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
        QSqlQuery createQuery{query, *this};
        if (!createQuery.exec()) {
            qFatal(qPrintable("Couldn't execute query!" + createQuery.lastError().text()));
        }
    }

    tablesWasCreated_ = true;
}
