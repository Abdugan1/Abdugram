#include "sqlquery.h"
#include "databaseclient.h"
#include "database.h"

SqlQuery::SqlQuery(const QString &query)
    : QSqlQuery{query, *database()->threadDb()}
{
}
