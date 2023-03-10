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

void Database::executeAllSqlFilesInRootDir(const QString &rootPath,
                                           const QString &sqlFileName)
{
    QDir::Filters filters = QDir::Dirs | QDir::NoDotAndDotDot;
    QDirIterator::IteratorFlag iterFlag = QDirIterator::Subdirectories;

    QDirIterator dirIterator(rootPath, filters, iterFlag);
    while (dirIterator.hasNext()) {
        QString query = findAndGetSqlQuery(dirIterator.next(), sqlFileName);
        QSqlError error = executeQuery(query);
        if (error.isValid())
            qWarning() << "Couldn't execute query" << query << error.text();
    }
}

QString Database::findAndGetSqlQuery(const QString &dirName, const QString &sqlFileName)
{
    QString query;
    QDir currentDir{dirName};
    auto fileNamesInCurrentDir = currentDir.entryList(QDir::Files);

    for (const auto &fileName : fileNamesInCurrentDir) {
        if (fileName == sqlFileName) {
            query = getSqlQueryStr(currentDir.filePath(fileName));
            break;
        }
    }

    return query;
}

void Database::connectToDatabase()
{
#if defined(API_SQL_CLIENT_LIBRARY)
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(".sql/" + DbName);
#elif defined(API_SQL_SERVER_LIBRARY)
        db_ = QSqlDatabase::addDatabase("QMYSQL");

        db_.setHostName(HostName);
        db_.setDatabaseName(DbName);
        db_.setUserName(UserName);
        db_.setPassword(Password);
#endif

    if (!db_.open()) {
        qCritical() << "Failed to connect to db!" << db_.lastError().text();
    } else {
        createTables();
    }
}

QString Database::getSqlQueryStr(const QString &sqlFileName)
{
    QString query;
    QFile file{sqlFileName};

    if (file.open(QFile::ReadOnly))
        query = file.readAll();
    else
        qWarning() << "Couldn't open file:" << sqlFileName << file.errorString();

    return query;
}

QSqlError Database::executeQuery(const QString &queryStr)
{
    QSqlQuery query(queryStr);
    query.exec();
    return query.lastError();
}
