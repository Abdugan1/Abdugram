#include "serverlogger.h"

ServerLogger &ServerLogger::instance()
{
    static ServerLogger logger;
    return logger;
}


void ServerLogger::writeLog(const QString &log)
{
    QString l = log + "\n";
    QMutexLocker lock{&logFile_->mutex()};
    logFile_->write(l);
}
