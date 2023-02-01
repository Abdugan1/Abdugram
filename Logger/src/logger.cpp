#include "logger.h"

#include <iostream>
#include <QTextStream>
#include <QDateTime>

bool  Logger::isInit_   = false;
bool  Logger::echoMode_ = false;
QFile Logger::logFile_  = QFile();

QHash<QtMsgType, QString> Logger::contextNames_ = {
    {QtMsgType::QtDebugMsg,    "DBG"},
    {QtMsgType::QtInfoMsg,     "INF"},
    {QtMsgType::QtWarningMsg,  "WRN"},
    {QtMsgType::QtCriticalMsg, "CRT"},
    {QtMsgType::QtFatalMsg,    "FTL"}
};

void Logger::init(const QString &logFileName)
{
    if (isInit_)
        return;

    logFile_.setFileName(logFileName);
    logFile_.open(QFile::Append | QFile::Text);

    qInstallMessageHandler(Logger::messageOutput);

    isInit_ = true;
}

void Logger::clean()
{
    logFile_.close();
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


    logFile_.write(log.toLocal8Bit());
    logFile_.flush();

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
