#include "mainpage.h"
#include "sidepanel.h"
#include "conversationside.h"

#include <QDebug>

MainPage::MainPage(QWidget *parent)
    : QSplitter{parent}
{
    setupUi();
}

void MainPage::setupUi()
{
    sidePanel_        = new SidePanel;
    conversationSide_ = new ConversationSide;

    addWidget(sidePanel_);
    addWidget(conversationSide_);

    setHandleWidth(1);
}
