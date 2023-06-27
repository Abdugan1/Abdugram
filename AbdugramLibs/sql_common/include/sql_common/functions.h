#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SqlCommon_global.h"

#include <QString>
#include <functional>

class QDateTime;
class QSqlQuery;

enum class ErrorImportance {
    Info,
    Debug,
    Warning,
    Critical,
    Fatal,
};

SQLCOMMON_EXPORT extern QString readFullFile(const QString &fileName);

SQLCOMMON_EXPORT extern bool executeQuery(QSqlQuery &query, ErrorImportance errorImportance);

SQLCOMMON_EXPORT extern bool executeTransaction(std::function<bool()> callable);

#endif // FUNCTIONS_H
