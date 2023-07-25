#ifndef SQLQUERY_H
#define SQLQUERY_H

#include "SqlClient_global.h"

#include <QSqlQuery>

class SQLCLIENT_EXPORT SqlQuery : public QSqlQuery
{
public:
    explicit SqlQuery(const QString& query = QString{});
};

#endif // SQLQUERY_H
