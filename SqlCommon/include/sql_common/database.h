#ifndef DATABASE_H
#define DATABASE_H

#include "SqlCommon_global.h"
#include <QSqlDatabase>

class SQLCOMMON_EXPORT Database
{
public:
    virtual ~Database();

    virtual void connectToDatabase() = 0;

protected:
    Database() = default;

    virtual void createTables() = 0;

    static void executeAllSqlFilesInRootDir(const QString &rootPath, const QString &sqlFileName);
    static QString findAndGetSqlQuery(const QString &dirName, const QString &sqlFileName);
    static QString getSqlQueryStr(const QString &sqlFileName);

private:
    static QSqlError executeQuery(const QString &queryStr);

private:
    static QSqlDatabase db_;
};

#endif // DATABASE_H
