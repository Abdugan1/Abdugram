#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QRegularExpression>
#include <QDebug>

#include <api_client/test.h>
#include <api_sql_client/database.h>

#include <logger/logger.h>

#include "ui/mainwindow.h"

void setupStyleSheet(QString rawStyleSheet)
{
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

    // Setup logger
    Logger::init();
    Logger::setEchoMode(true);

    // Setting qss
    QFile qssFile(":/qss/style.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        setupStyleSheet(qssFile.readAll());
    } else {
        qDebug() << "Could not read file";
    }

    // Setting fonts
    QFontDatabase::addApplicationFont(":/fonts/Montserrat-Regular.ttf");
    QFontDatabase db;
    app.setFont(QFont{"Montserrat", 12, QFont::Medium});

    Database::connectToDatabase();

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
