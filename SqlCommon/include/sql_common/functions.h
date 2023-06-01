#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
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

#endif // FUNCTIONS_H
