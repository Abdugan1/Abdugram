#ifndef SERVERLOGGER_H
#define SERVERLOGGER_H

#include <logger/logger.h>

class ServerLogger : public Logger
{
public:
    static ServerLogger &instance();

    void writeLog(const QString &log) override;
};

#endif // SERVERLOGGER_H
