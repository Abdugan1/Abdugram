#include "logfile.h"

#include <QMutexLocker>
#include <QFileInfo>
#include <QDebug>

LogFile::LogFile()
{

}

LogFile::LogFile(const QString &fileName)
{
    setFileName(fileName);
}

QMutex &LogFile::mutex()
{
    return mutex_;
}

void LogFile::setFileName(const QString &fileName)
{
    file_.setFileName(fileName);

    if (!file_.open(QFile::ReadWrite | QFile::Append | QFile::Text)) {
        qCritical() << "Couldn't open file:" << fileName << "!" << file_.errorString();
    }
}

QString LogFile::filePath()
{
    QString fname = file_.fileName();
    return QFileInfo(fname).absoluteFilePath();
}

void LogFile::write(const QString &log)
{
    QTextStream fileStream{&file_};
    fileStream << log;
}

QString LogFile::readAll()
{
    QString data = file_.readAll();
    return data;
}

QString LogFile::readLine()
{
    QString data = file_.readLine();
    return data;
}

void LogFile::moveToBegin()
{
    file_.seek(0);
}

void LogFile::moveToEnd()
{
    file_.seek(file_.size());
}

bool LogFile::atEnd()
{
    bool e = file_.atEnd();
    return e;
}
