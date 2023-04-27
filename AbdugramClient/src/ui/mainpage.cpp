#include "mainpage.h"
#include "sidepanel.h"
#include "mv/messagelistview.h"

#include <QDebug>

MainPage::MainPage(QWidget *parent)
    : QSplitter{parent}
{
    setupUi();

    connect(sidePanel_, &SidePanel::searchOnServerRequested,
            this,       &MainPage::searchOnServerRequested);

    connect(sidePanel_, &SidePanel::searchOnLocalRequested,
            this,       &MainPage::searchOnLocalRequested);
}

void MainPage::setupUi()
{
    sidePanel_       = new SidePanel;
    messageListView_ = new MessageListView;

    addWidget(sidePanel_);
    addWidget(messageListView_);

    setHandleWidth(1);
}
