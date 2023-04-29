#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QSplitter>

#include "net_common/messages/abdumessage.h"

class SidePanel;
class MessageListView;

class MainPage : public QSplitter
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);

private:
    void setupUi();

private:
    SidePanel       *sidePanel_       = nullptr;
    MessageListView *messageListView_ = nullptr;
};

#endif // MAINPAGE_H
