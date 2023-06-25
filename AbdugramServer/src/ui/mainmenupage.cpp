#include "ui/mainmenupage.h"
#include "ui/titledwindow.h"
#include "ui/cursedwindow.h"

#include <net_common/consts.h>

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
    statusWindow_ = WindowPtr{new CursedWindow{workingWindow()->width() - 20, 0, 20, 5,
            workingWindow(), WindowType::DerWindow}};
    statusWindow_->box();
    printServerStatus();
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
    switch (currentItem->index) {
    case 0:
        choiceParse_(this, "toggle_server");
        break;
    case 1:
        choiceParse_(this, "show_logs");
        break;
    case 2:
        choiceParse_(this, "quit");
        break;
    }
}

void MainMenuPage::printServerStatus()
{
    std::string serverStatus  = "Status: "
            + std::string(serverRunning_ ? "running" : "stopped");
    std::string serverAddress = "Address: ";
    std::string serverPort    = "Port: ";

    statusWindow_->print(1, 1, serverStatus);
    statusWindow_->print(1, 2, serverAddress);
    statusWindow_->print(1, 3, serverPort);
}

void MainMenuPage::setServerRunning(bool newServerRunning)
{
    serverRunning_ = newServerRunning;
    printServerStatus();
}
