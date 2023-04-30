#include "functions.h"

#include <QFile>
#include <QDateTime>
#include <QDebug>

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

const QString DateTimePattern = "yyyy-MM-dd HH:mm:ss";

QDateTime stringToDateTime(const QString &dateTimeString)
{
    return QDateTime::fromString(dateTimeString, DateTimePattern);
}
