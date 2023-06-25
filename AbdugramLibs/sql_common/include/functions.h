#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

extern QString readFullFile(const QString &fileName);

extern bool executeQuery(QSqlQuery &query, ErrorImportance errorImportance);

extern bool executeTransaction(std::function<bool()> callable);

#endif // FUNCTIONS_H
