#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QRegularExpression>
#include <QDebug>

#include <net_common/messages/abdumessage.h>
#include <net_common/tcpsession.h>

#include <sql_client/databaseclient.h>

#include <logger/logger.h>

#include "ui/mainwindow.h"

void setupStyleSheet(const QString &qssFileName)
{
    QFile qssFile(qssFileName);
    if (!qssFile.open(QFile::ReadOnly)) {
        qDebug() << "Could not read file";
        return;
    }
    QString rawStyleSheet = qssFile.readAll();

    QFile styleVarsFile(":/qss/style_vars.txt");
    if (!styleVarsFile.open(QFile::ReadOnly)) {
        qDebug() << "Could not open" << styleVarsFile.fileName();
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
    }

    using Regex      = QRegularExpression;
    using RegexMatch = QRegularExpressionMatch;
    Regex      varRegex{"(\\@[a-zA-Z]+)\\s*\\=\\s*(.*)\\;"};
    RegexMatch match;

    while (!styleVarsFile.atEnd()) {
        QString var = styleVarsFile.readLine();
        match = varRegex.match(var);
        if (!match.hasMatch())
            continue;

        QString varName = match.captured(1);
        QString varVal  = match.captured(2);

        rawStyleSheet.replace(varName, varVal);
    }

    qApp->setStyleSheet(rawStyleSheet);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qRegisterMetaType<AbduMessagePtr>("AbduMessagePtr");

    // Setup logger
    Logger::init();
    Logger::setEchoMode(true);

    // Setting qss
    setupStyleSheet(":/qss/style.qss");

    // Setting fonts
    QFontDatabase::addApplicationFont(":/fonts/Montserrat-Regular.ttf");
    QFontDatabase db;
    app.setFont(QFont{"Montserrat", 12, QFont::Medium});

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
