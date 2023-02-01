#include "mainmenupage.h"
#include "titledwindow.h"
#include "cursedwindow.h"

#include <QCoreApplication>

inline const int Enter = 10;

MainMenuPage::MainMenuPage()
    : TitledWindow("Main Menu")
{
    const char *choices[] = {
        "Toggle server",
        "Show logs",
        "Exit"
    };

    // Configuring ITEMS
    const int n = sizeof(choices) / sizeof(choices[0]);
    items_.resize(n + 1);
    for (int i = 0; i < n; ++i)
        items_[i] = new_item(choices[i], "");

    // Creating menu
    menu_= new_menu(&items_[0]);

    // Configuring menu windows
    set_menu_win(menu_, pwindowRaw());
    set_menu_sub(menu_, pworkingWindowRaw());

    post_menu(menu_);

    //
    statusWindow_ = WindowPtr{new CursedWindow{5, 5, 5, 5,
            workingWindow(), WindowType::DerWindow}};
    statusWindow_->box();
}

void MainMenuPage::parseInput(int input)
{
    switch (input) {
    case KEY_DOWN:
        menu_driver(menu_, REQ_DOWN_ITEM);
        break;
    case KEY_UP:
        menu_driver(menu_, REQ_UP_ITEM);
        break;
    case Enter:
        doCurrentItemAction();
        break;
    }
}

void MainMenuPage::doCurrentItemAction()
{
    ITEM *currentItem = current_item(menu_);
    mvwprintw(pworkingWindowRaw(), 4, 4, std::to_string(currentItem->index).c_str());
    switch (currentItem->index) {
    case 2:
        choiceParse_(this, "quit");
        break;
    }
}
