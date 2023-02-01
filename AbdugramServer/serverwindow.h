#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QRunnable>
#include <memory>
#include <any>

class TitledWindow;
class MainMenuPage;

class ServerWindow : public QRunnable
{
private:
    template <typename T>
    using Pointer = std::shared_ptr<T>;

public:
    explicit ServerWindow();
    ~ServerWindow();

    void run() override;

private:
    void init();

    void printCurrentPage();
    void getAndParseInput();

    // Parse results from windows
    void resultFunction(TitledWindow *window, const std::any &value);

    // MainMenu
    void parseMainMenuResults(const std::any &value);


private:
    bool alive_ = true;

    Pointer<MainMenuPage> mainMenu_;

    Pointer<TitledWindow> currentPage_;
};

#endif // SERVERWINDOW_H
