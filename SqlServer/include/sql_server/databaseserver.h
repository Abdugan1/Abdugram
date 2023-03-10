#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include "SqlServer_global.h"
#include <sql_common/database.h>

class SQLSERVER_EXPORT DatabaseServer : public Database
{
public:
    static DatabaseServer *instance();

    void connectToDatabase() override;

protected:
    void createTables() override;
};

#endif // DATABASESERVER_H
