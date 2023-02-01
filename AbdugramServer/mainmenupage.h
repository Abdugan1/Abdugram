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

private:
    void doCurrentItemAction();

private:
    MENU *menu_;
    std::vector<ITEM *> items_;

    WindowPtr statusWindow_;
};

#endif // MAINMENUPAGE_H
