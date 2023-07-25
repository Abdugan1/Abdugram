#include "ui/sidepanel.h"
#include "ui/imagebutton.h"
#include "ui/searchlineedit.h"

#include "ui/mv/chatlistview.h"

#include <sql_common/data_structures/chat.h>

#include <sql_client/databaseclient.h>

#include <QBoxLayout>
#include <QDebug>

SidePanel::SidePanel(QWidget *parent)
    : QFrame{parent}
{
    setupUi();

    connect(searchLineEdit_, &SearchLineEdit::searchIsEmpty, chatListView_, &ChatListView::setMainModel);
    
    connect(chatListView_, &ChatListView::selectionWasChangedByUser, this, &SidePanel::selectionWasChanged);
    connect(chatListView_, &ChatListView::selectionWasChangedByUser, this, [this]() {
        chatListView_->update(chatListView_->currentIndex());
    });

    connect(chatListView_, &ChatListView::newChatItemAdded, this, &SidePanel::newChatItemAdded);
}

void SidePanel::clearChatSelection()
{
    const auto prevIndex = chatListView_->currentIndex();
    chatListView_->clearSelection();
    chatListView_->update(prevIndex);
}

void SidePanel::setupUi()
{
    sideMenuButton_ = new ImageButton{QPixmap{":/images/drawer_button.png"}};
    connect(sideMenuButton_, &ImageButton::clicked, this, &SidePanel::sideMenuRequested);

    searchLineEdit_ = new SearchLineEdit;
    searchLineEdit_->setPlaceholderText(tr("Search"));

    QHBoxLayout *hLayout = new QHBoxLayout;
    const int m = 8;
    hLayout->setContentsMargins(m, m, m, m);
    hLayout->setSpacing(m);
    hLayout->addWidget(sideMenuButton_);
    hLayout->addWidget(searchLineEdit_);

    chatListView_ = new ChatListView;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(chatListView_);

    setLayout(vLayout);
}
