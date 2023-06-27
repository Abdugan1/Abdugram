#ifndef LOGGER_H
#define LOGGER_H

#include "Logger_global.h"

#include <QString>
#include <QHash>

#include "logfile.h"

class LOGGER_EXPORT Logger
{
public:
    virtual ~Logger();

    virtual void writeLog(const QString &log) = 0;

    void setLogFile(LogFilePtr &logFile);

    static void init(const QString &logFileName = "./logs.log");

    static bool echoMode();
    static void setEchoMode(bool newEchoMode);

protected:
    Logger() = default;
    Logger(const Logger &) = delete;
    Logger& operator=(const Logger &) = delete;

private:

    static void messageOutput(QtMsgType type,
                              const QMessageLogContext &context,
                              const QString &message);

protected:
    LogFilePtr logFile_;

private:
    static bool    isInit_;
    static bool    echoMode_;
    static LogFile defaultLogFile_;
    static QHash<QtMsgType, QString> contextNames_;
};

#endif // LOGGER_H
