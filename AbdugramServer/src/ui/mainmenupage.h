#ifndef MAINMENUPAGE_H
#define MAINMENUPAGE_H

#include <vector>
#include "titledwindow.h"
#include <ncursesw/menu.h>

class MainMenuPage : public TitledWindow
{
public:
    explicit MainMenuPage();

    void parseInput(int choice) override;

    void setServerRunning(bool newServerRunning);

private:
    void doCurrentItemAction();

    void printServerStatus();

private:
    MENU *menu_;
    std::vector<ITEM *> items_;

    WindowPtr statusWindow_;
    bool serverRunning_ = false;
};

#endif // MAINMENUPAGE_H
