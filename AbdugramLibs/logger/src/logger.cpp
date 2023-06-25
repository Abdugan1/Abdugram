#include "logger.h"

#include <iostream>
#include <QTextStream>
#include <QDateTime>

bool    Logger::isInit_          = false;
bool    Logger::echoMode_        = false;
LogFile Logger::defaultLogFile_  = LogFile{};

QHash<QtMsgType, QString> Logger::contextNames_ = {
    {QtMsgType::QtDebugMsg,    "DBG"},
    {QtMsgType::QtInfoMsg,     "INF"},
    {QtMsgType::QtWarningMsg,  "WRN"},
    {QtMsgType::QtCriticalMsg, "CRT"},
    {QtMsgType::QtFatalMsg,    "FTL"}
};

Logger::~Logger()
{

}

void Logger::setLogFile(LogFilePtr &logFile)
{
    logFile_ = logFile;
}

void Logger::init(const QString &logFileName)
{
    if (isInit_)
        return;

    defaultLogFile_.setFileName(logFileName);

    qInstallMessageHandler(Logger::messageOutput);

    isInit_ = true;
}

void Logger::messageOutput(QtMsgType type,
                           const QMessageLogContext &context,
                           const QString &message)
{
    // %1 - Date time
    // %2 - Log LVL
    // %3 - File name
    // %4 - Function name
    // %5 - Line
    // %6 - Context
    QString log = QString("%1 | %2 | %3 | %4 | %5\n")
            .arg(QDateTime::currentDateTime().toString(Qt::ISODate))
            .arg(contextNames_.value(type))
            .arg(context.file)
            .arg(context.function)
            .arg(message);


    defaultLogFile_.write(log.toLocal8Bit());

    if (echoMode_)
        QTextStream(stdout) << log;
}

bool Logger::echoMode()
{
    return echoMode_;
}

void Logger::setEchoMode(bool newEchoMode)
{
    echoMode_ = newEchoMode;
}
