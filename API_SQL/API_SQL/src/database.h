#ifndef DATABASE_H
#define DATABASE_H

#include "API_SQL_global.h"
#include <QSqlDatabase>

class API_SQL_EXPORT Database
{
public:
    ~Database();

    static void connectToDatabase();

private:
    Database() = default;

    static void createTables();
    static void findInDirCreateSqlFilesAndExecute(const QString &dirName);
    static void findInDirConstraintsSqlFilesAndExecute(const QString &dirName);

private:
    static QSqlError executeQuery(const QString &queryStr);

private:
    static QSqlDatabase db_;
};

#endif // DATABASE_H
