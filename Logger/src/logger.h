#ifndef LOGGER_H
#define LOGGER_H

#include "Logger_global.h"

#include <QString>
#include <QFile>
#include <QHash>

class LOGGER_EXPORT Logger
{
public:
    static void init(const QString &logFileName = "./logs.log");
    static void clean();

    static bool echoMode();
    static void setEchoMode(bool newEchoMode);

private:
    Logger() = default;

    static void messageOutput(QtMsgType type,
                              const QMessageLogContext &context,
                              const QString &message);

private:
    static bool  isInit_;
    static bool  echoMode_;
    static QFile logFile_;
    static QHash<QtMsgType, QString> contextNames_;
};

#endif // LOGGER_H
