#include "cursedwindow.h"

#include <cassert>
#include <string>

CursedWindow::CursedWindow(int x, int y, int w, int h)
{
    init(x, y, w, h, nullptr, WindowType::Window);
}

CursedWindow::CursedWindow()
{
    init(0, 0, COLS, LINES, nullptr, WindowType::Window);
}

CursedWindow::CursedWindow(int x, int y, int w, int h,
                           WindowPtr parent,
                           WindowType winType)
{
    if (parent != nullptr) {
        assert((winType == WindowType::SubWindow)
               || (winType == WindowType::DerWindow));
    }
    init(x, y, w, h, parent, winType);
}

void CursedWindow::refresh()
{
    wrefresh(window_);
}

void CursedWindow::clear()
{
    werase(window_);
}

void CursedWindow::print(int x, int y, const std::string &str)
{
    mvwprintw(window_, y, x, str.c_str());
}

WINDOW *CursedWindow::pwindow()
{
    return window_;
}

int CursedWindow::box(chtype v, chtype h)
{
    return ::box(window_, v, h);
}

int CursedWindow::x() const
{
    return x_;
}

int CursedWindow::y() const
{
    return y_;
}

int CursedWindow::width() const
{
    return w_;
}

int CursedWindow::height() const
{
    return h_;
}

void CursedWindow::init(int x, int y, int w, int h,
                        WindowPtr parent,
                        WindowType winType)
{
    assert((winType >= WindowType::Window) && (winType <= WindowType::DerWindow));

    x_ = x;
    y_ = y;
    h_ = h;
    w_ = w;

    switch (winType) {
    case WindowType::Window:
    {
        window_ = newwin(h, w, y, x);
        break;
    }
    case WindowType::SubWindow:
    {
        WINDOW *p = parent->pwindow();
        window_ = subwin(p, h, w, y, x);
        break;
    }
    case WindowType::DerWindow:
    {
        WINDOW *p = parent->pwindow();
        window_ = derwin(p, h, w, y, x);
        break;
    }
    }
}
