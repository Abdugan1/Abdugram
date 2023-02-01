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

void Database::createTables()
{
    qDebug() << "Creating tables...";

    // Iterating through all sql directiries and exec create.sql files
    const QString rootPath("./.sql");
    QDir::Filters filters = QDir::Dirs | QDir::NoDotAndDotDot;
    QDirIterator::IteratorFlag iterFlag = QDirIterator::Subdirectories;

    QDirIterator dirIteratorCreate(rootPath, filters, iterFlag);
    while (dirIteratorCreate.hasNext()) {
        findInDirCreateSqlFilesAndExecute(dirIteratorCreate.next());
    }


#ifdef API_SQL_SERVER_LIBRARY
    QDirIterator dirIteratorConstraints(rootPath, filters, iterFlag);
    while (dirIteratorConstraints.hasNext()) {
        findInDirConstraintsSqlFilesAndExecute(dirIteratorConstraints.next());
    }
#endif
}

void Database::findInDirCreateSqlFilesAndExecute(const QString &dirName)
{
    QDir currentDir(dirName);
    QStringList dirFileNames = currentDir.entryList(QDir::Files);

    for (const auto &fileName : dirFileNames) {
        if (fileName == "create.sql") {
            QFile file(currentDir.filePath(fileName));

            qDebug() << file.fileName();
            if (!file.open(QFile::ReadOnly)) {
                qCritical() << "Couldn't read file!" << file.fileName();
                continue;
            }

            QString queryStr = file.readAll();
            QSqlError error = executeQuery(queryStr);
            if (error.isValid()) {
                qCritical() << "Couldn't create" << file.fileName() << error.text();
            }
        }
    }
}

void Database::findInDirConstraintsSqlFilesAndExecute(const QString &dirName)
{
    QDir currentDir(dirName);
    QStringList dirFileNames = currentDir.entryList(QDir::Files);

    for (const auto &fileName : dirFileNames) {
        if (fileName == "constraints.sql") {
            QFile file(currentDir.filePath(fileName));

            qDebug() << file.fileName();
            if (!file.open(QFile::ReadOnly)) {
                qCritical() << "Couldn't read file!" << file.fileName();
                continue;
            }

            QString queryStr = file.readAll();
            QSqlError error = executeQuery(queryStr);
            if (error.isValid()) {
                qCritical() << "Couldn't create" << file.fileName() << error.text();
            }
        }
    }
}

QSqlError Database::executeQuery(const QString &queryStr)
{
    QSqlQuery query(queryStr);
    query.exec();
    return query.lastError();
}
