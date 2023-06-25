#include "functions.h"

#include <QFile>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void logError(const QString &log, ErrorImportance errorImportance)
{
    switch (errorImportance) {
    case ErrorImportance::Info:     qInfo()     << log;                break;
    case ErrorImportance::Debug:    qDebug()    << log;                break;
    case ErrorImportance::Warning:  qWarning()  << log;                break;
    case ErrorImportance::Critical: qCritical() << log;                break;
    case ErrorImportance::Fatal:    qFatal("%s", log.toStdString().c_str()); break;
    }
}

QString readFullFile(const QString &fileName)
{
    QString content;
    QFile file{fileName};

    if (file.open(QFile::ReadOnly | QFile::Text))
        content = file.readAll();
    else
        qWarning() << "Couldn't open file" << fileName << file.errorString();

    return content;
}

bool executeQuery(QSqlQuery &query, ErrorImportance errorImportance)
{
    if (!query.exec()) {
        logError("Couldn't execute query \"" + query.executedQuery() + "\"" +
                 "Error: \"" + query.lastError().text() + "\"", errorImportance);
        return false;
    }
    return true;
}

bool executeTransaction(std::function<bool ()> callable)
{
    QSqlDatabase::database().transaction();

    bool success = callable();

    if (success) {
        if (!QSqlDatabase::database().commit()) {
            QSqlDatabase::database().rollback();
            success = false;
        }
    } else {
        QSqlDatabase::database().rollback();
    }

    return success;
}
