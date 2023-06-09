#include "mainpage.h"
#include "sidepanel.h"
#include "conversationside.h"

#include <QDebug>

MainPage::MainPage(QWidget *parent)
    : QSplitter{parent}
{
    setupUi();

    connect(sidePanel_, &SidePanel::selectionWasChanged, conversationSide_, &ConversationSide::setCurrentChat);
    connect(sidePanel_, &SidePanel::newChatItemAdded,    conversationSide_, &ConversationSide::checkCurrentChat);
}

void MainPage::setupUi()
{
    sidePanel_        = new SidePanel;
    conversationSide_ = new ConversationSide;

    addWidget(sidePanel_);
    addWidget(conversationSide_);

    setHandleWidth(1);
}
