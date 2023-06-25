#include "ui/serverwindow.h"
#include "ui/mainmenupage.h"
#include "ui/logsviewpage.h"

#include <QCoreApplication>
#include <QDebug>

ServerWindow::ServerWindow(LogFilePtr &serverLogsFile)
{
    init(serverLogsFile);
}
ServerWindow::~ServerWindow()
{
    endwin();
    qDebug() << "~ServerWindow";
}

void ServerWindow::run()
{
    while (alive_) {
        printCurrentPage();
        getAndParseInput();
    }
    QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
}

void ServerWindow::setMainMenuServerStatus(bool serverRunning)
{
    mainMenu_->setServerRunning(serverRunning);
}

void ServerWindow::updateLogsView()
{
    logsView_->updateBuffer();
}

void ServerWindow::init(LogFilePtr &serverLogsFile)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh(); // without this nothing will work!

    mainMenu_ = Pointer<MainMenuPage>(new MainMenuPage());
    mainMenu_->setChoiceParse([this](TitledWindow *window, const std::string &value) {
        resultFunction(window, value);
    });

    logsView_ = Pointer<LogsViewPage>(new LogsViewPage{serverLogsFile});
    logsView_->setChoiceParse([this](TitledWindow *window, const std::string &value) {
        resultFunction(window, value);
    });

    currentPage_ = mainMenu_;
}

void ServerWindow::printCurrentPage()
{
    currentPage_->refresh();
}

void ServerWindow::getAndParseInput()
{
    wtimeout(currentPage_->pwindowRaw(), 1000 / 24 /*24fps*/);
    int input = wgetch(currentPage_->pwindowRaw());
    currentPage_->parseInput(input);
}

void ServerWindow::resultFunction(TitledWindow *window, const std::any &value)
{
    if (window == mainMenu_.get()) {
        parseMainMenuResults(value);
    } else if (window == logsView_.get()) {
        parseLogsViewResults(value);
    }
}

void ServerWindow::parseMainMenuResults(const std::any &value)
{
    std::string result = std::any_cast<std::string>(value);
    if (result == "quit") {
        alive_ = false;
        return;
    }

    if (result == "toggle_server") {
        emit toggleServerRequested();
    } else if (result == "show_logs") {
        currentPage_ = logsView_;
    }
}

void ServerWindow::parseLogsViewResults(const std::any &value)
{
    std::string result = std::any_cast<std::string>(value);
    if (result == "quit")
        currentPage_ = mainMenu_;
}
