#ifndef LOGFILE_H
#define LOGFILE_H

#include "Logger_global.h"

#include <QFile>
#include <QMutex>
#include <QSharedPointer>

class LogFile;
using LogFilePtr = QSharedPointer<LogFile>;

class LOGGER_EXPORT LogFile : public QMutex
{
public:
    explicit LogFile();
    explicit LogFile(const QString &fileName);

    QMutex &mutex();

    void setFileName(const QString &fileName);
    QString filePath();

    void write(const QString &log);
    QString readAll();
    QString readLine();

    void moveToBegin();
    void moveToEnd();

    bool atEnd();

private:
    QFile   file_;
    QMutex  mutex_;
};

#endif // LOGFILE_H
