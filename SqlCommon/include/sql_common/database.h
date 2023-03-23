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

private:
    static QSqlError executeQuery(const QString &queryStr);

private:
    static QSqlDatabase db_;
};

extern QString readFullFile(const QString &fileName);

#endif // DATABASE_H
