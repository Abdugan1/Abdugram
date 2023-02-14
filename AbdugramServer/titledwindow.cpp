#include "titledwindow.h"
#include "cursedwindow.h"

#include <cstring>

TitledWindow::TitledWindow(int x, int y, int w, int h,
                           WindowPtr parent,
                           WindowType winType,
                           const std::string &title)
{
    init(x, y, w, h, parent, winType, title);
}

TitledWindow::TitledWindow(const std::string &title)
{
    init(0, 0, COLS, LINES, nullptr, WindowType::Window, title);
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

const WindowPtr &TitledWindow::workingWindow() const
{
    return workingWindow_;
}


const WindowPtr &TitledWindow::window() const
{
    return outerFrame_;
}

WindowPtr &TitledWindow::rworkingWindow()
{
    return workingWindow_;
}


WindowPtr &TitledWindow::rwindow()
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

void TitledWindow::init(int x, int y, int w, int h,
                        WindowPtr parent,
                        WindowType winType,
                        const std::string &title)
{
    title_ = title;
    outerFrame_ = WindowPtr{new CursedWindow{x, y, w, h, parent, winType}};

    constructInnerWindow();
    constructWorkingWindow();

    keypad(pwindowRaw(), true);
    keypad(pworkingWindowRaw(), true);
}

void TitledWindow::constructInnerWindow()
{
    int x = 0;
    int y = 2;
    int w = outerFrame_->width();
    int h = outerFrame_->height() - 2;

    innerFrame_ = WindowPtr{new CursedWindow{x, y, w, h, outerFrame_,
                                            WindowType::DerWindow}};
}

void TitledWindow::constructWorkingWindow()
{
    int x = 1;
    int y = 1;
    int w = innerFrame_->width()  - 2;
    int h = innerFrame_->height() - 2;

    workingWindow_ = WindowPtr{new CursedWindow{x, y, w, h, innerFrame_,
                                                WindowType::DerWindow}};
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
    int x = (innerFrame_->width() - title.size()) / 2;
    int y = 1;
    outerFrame_->print(x, y, title);
}

void TitledWindow::setChoiceParse(std::function<void (TitledWindow *,
                                                      const std::string &)>
                                  newChoiceParse)
{
    choiceParse_ = newChoiceParse;
}
