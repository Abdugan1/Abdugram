#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class SqlDatabase : public QSqlDatabase
{
public:
    explicit SqlDatabase();

    int ownId() const;
    void setOwnId(int newOwnId);

    void connect();

private:
    void createTables();

private:
    int ownId_ = -1;

    static bool tablesWasCreated_;
    static int databaseId_;
};

#endif // DATABASE_H
