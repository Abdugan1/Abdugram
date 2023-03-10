#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H

#include "SqlClient_global.h"
#include <sql_common/database.h>

class SQLCLIENT_EXPORT DatabaseClient : public Database
{
public:
    static DatabaseClient *instance();

    void connectToDatabase() override;

protected:
    void createTables() override;
};

#endif // DATABASECLIENT_H
