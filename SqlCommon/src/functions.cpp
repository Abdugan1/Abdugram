#include "functions.h"

#include <QFile>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
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
