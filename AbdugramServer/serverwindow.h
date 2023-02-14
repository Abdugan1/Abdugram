#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QObject>
#include <memory>
#include <any>

class TitledWindow;
class MainMenuPage;
class LogsViewPage;

class ServerWindow : public QObject
{
    Q_OBJECT
private:
    template <typename T>
    using Pointer = std::shared_ptr<T>;

public:
    explicit ServerWindow();
    ~ServerWindow();

signals:
    void toggleServerRequested();

public slots:
    void run();

    void setMainMenuServerStatus(bool serverRunning);

private:
    void init();

    void printCurrentPage();
    void getAndParseInput();

    // Parse results from windows
    void resultFunction(TitledWindow *window, const std::any &value);

    //
    void parseMainMenuResults(const std::any &value);
    void parseLogsViewResults(const std::any &value);


private:
    bool alive_ = true;

    Pointer<TitledWindow> currentPage_;

    Pointer<MainMenuPage> mainMenu_;
    Pointer<LogsViewPage> logsView_;
};

#endif // SERVERWINDOW_H
