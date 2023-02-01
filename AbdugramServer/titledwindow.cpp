#include "titledwindow.h"
#include "cursedwindow.h"

#include <cstring>

TitledWindow::TitledWindow(int h, int w, int y, int x,
                           WindowPtr parent,
                           WindowType winType,
                           const std::string &title)
{
    init(h, w, y, x, parent, winType, title);
}

TitledWindow::TitledWindow(const std::string &title)
{
    init(LINES, COLS, 0, 0, nullptr, WindowType::Window, title);
}

void TitledWindow::refresh()
{
    printFrame();
    outerFrame_->refresh();
    innerFrame_->refresh();
    workingWindow_->refresh();
}

void TitledWindow::parseInput(int choice)
{
    (void)choice;
}

WindowPtr TitledWindow::workingWindow()
{
    return workingWindow_;
}

WindowPtr TitledWindow::window()
{
    return outerFrame_;
}

WINDOW *TitledWindow::pworkingWindowRaw()
{
    return workingWindow_->pwindow();
}

WINDOW *TitledWindow::pwindowRaw()
{
    return outerFrame_->pwindow();
}

void TitledWindow::init(int h, int w, int y, int x,
                        WindowPtr parent,
                        WindowType winType,
                        const std::string &title)
{
    title_ = title;
    outerFrame_ = std::make_shared<CursedWindow>(h, w, y, x, parent, winType);

    constructInnerWindow();
    constructWorkingWindow();

    keypad(pwindowRaw(), true);
    keypad(pworkingWindowRaw(), true);
}

void TitledWindow::constructInnerWindow()
{
    int h = outerFrame_->height() - 2;
    int w = outerFrame_->width();
    int y = 2;
    int x = 0;

    innerFrame_ = std::make_shared<CursedWindow>(h, w, y, x,
                                                 outerFrame_,
                                                 WindowType::DerWindow);
}

void TitledWindow::constructWorkingWindow()
{
    int h = innerFrame_->height() - 2;
    int w = innerFrame_->width()  - 2;
    int y = 1;
    int x = 1;

    workingWindow_ = std::make_shared<CursedWindow>(h, w, y, x,
                                                    innerFrame_,
                                                    WindowType::DerWindow);
}

void TitledWindow::printFrame()
{
    printTitle();
    innerFrame_->box();
    outerFrame_->box();
}

void TitledWindow::printTitle()
{
    std::string title = "==" + title_ + "==";
    int y = 1;
    int x = (innerFrame_->width() - title.size()) / 2;
    mvwprintw(outerFrame_->pwindow(), y, x, title.c_str());
}

void TitledWindow::setChoiceParse(std::function<void (TitledWindow *,
                                                      const std::string &)>
                                  newChoiceParse)
{
    choiceParse_ = newChoiceParse;
}
