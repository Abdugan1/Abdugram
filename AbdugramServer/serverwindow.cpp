#include "serverwindow.h"
#include "mainmenupage.h"

#include <QCoreApplication>
#include <QDebug>

ServerWindow::ServerWindow()
{
    init();
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

void ServerWindow::init()
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
    }
}

void ServerWindow::parseMainMenuResults(const std::any &value)
{
    std::string result = std::any_cast<std::string>(value);
    if (result == "quit") {
        alive_ = false;
    }
}
