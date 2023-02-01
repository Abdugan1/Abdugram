#include "cursedwindow.h"

#include <cassert>

CursedWindow::CursedWindow(int h, int w, int y, int x)
{
    init(h, w, y, x, nullptr, WindowType::Window);
}

CursedWindow::CursedWindow()
{
    init(LINES, COLS, 0, 0, nullptr, WindowType::Window);
}

CursedWindow::CursedWindow(int h, int w, int y, int x,
                           WindowPtr parent,
                           WindowType winType)
{
    if (parent != nullptr) {
        assert((winType == WindowType::SubWindow)
               || (winType == WindowType::DerWindow));
    }
    init(h, w, y, x, parent, winType);
}

void CursedWindow::refresh()
{
    wrefresh(window_);
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

void CursedWindow::init(int h, int w, int y, int x,
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
