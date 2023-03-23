#include "database.h"

#include <QSqlQuery>
#include <QSqlError>

#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QDebug>

#if defined(API_SQL_CLIENT_LIBRARY)
const QString DbName = "abdugram";
#elif defined(API_SQL_SERVER_LIBRARY)
const QString HostName = "localhost";
const QString DbName   = "abdugram";
const QString UserName = "abdu";
const QString Password = "AbduganiYerzhanov002@!";
#endif

QSqlDatabase Database::db_ = QSqlDatabase();

Database::~Database()
{
    db_.close();
    qDebug() << "db closed";
}


