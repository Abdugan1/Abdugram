#ifndef CURSEDWINDOW_H
#define CURSEDWINDOW_H

#include <ncurses.h>
#include <memory>

enum class WindowType : int {
    Window,
    SubWindow,
    DerWindow
};

class CursedWindow;
using WindowPtr = std::shared_ptr<CursedWindow>;

//! Wrapper to raw cursed 'WINDOW'
class CursedWindow
{
public:
    //! Constructs sized window
    explicit CursedWindow(int h, int w, int y, int x);
    //! Constructs full sized window
    explicit CursedWindow();
    //! Constructs sized window by WindowType
    explicit CursedWindow(int h, int w, int y, int x, WindowPtr parent, WindowType winType);

    //! Refreshes 'WINDOW'
    void refresh();

    //! Returns raw cursed window type
    WINDOW *pwindow();

    //! Draws a box using chtypes
    int box(chtype v = 0, chtype h = 0);

    int x()      const;
    int y()      const;
    int width()  const;
    int height() const;

private:
    void init(int h, int w, int y, int x, WindowPtr parent, WindowType winType);

private:
    WINDOW *window_ = nullptr;
    int x_ = 0;
    int y_ = 0;
    int h_ = 0;
    int w_ = 0;
};

#endif // CURSEDWINDOW_H
