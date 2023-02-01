#ifndef TITLEDWINDOW_H
#define TITLEDWINDOW_H

#include <string>
#include <memory>
#include <functional>

#include "cursedwindow.h"

class CursedWindow;
enum class WindowType;
typedef struct _win_st WINDOW;

class TitledWindow
{
public:
    explicit TitledWindow(int h, int w, int y, int x,
                          WindowPtr parent,
                          WindowType winType,
                          const std::string &title);

    explicit TitledWindow(const std::string &title);

    void refresh();

    virtual void parseInput(int input);

    WindowPtr workingWindow();
    WindowPtr window();

    WINDOW *pworkingWindowRaw();
    WINDOW *pwindowRaw();

    void setChoiceParse(std::function<void (TitledWindow *,
                                            const std::string &)>
                        newChoiceParse);

protected:
    std::function<void(TitledWindow *, const std::string &)> choiceParse_;

private:
    void init(int h, int w, int y, int x,
              WindowPtr parent,
              WindowType winType,
              const std::string &title);

    void constructInnerWindow();
    void constructWorkingWindow();


    void printFrame();
    void printTitle();

private:
    std::string title_;
    WindowPtr outerFrame_;
    WindowPtr innerFrame_;
    WindowPtr workingWindow_;
};

#endif // TITLEDWINDOW_H
