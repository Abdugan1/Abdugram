#include "ui/components/chatlistside.h"
#include "ui/components/iconbutton.h"
#include "ui/components/searchlineedit.h"

#include "ui/components/colorrepository.h"

#include "ui/mv/chatlistview.h"

#include <sql_common/data_structures/chat.h>

#include <sql_client/databaseclient.h>

#include <QBoxLayout>
#include <QDebug>

ChatListSide::ChatListSide(QWidget *parent)
    : Widget{parent}
{
    setupUi();

    connect(searchLineEdit_, &SearchLineEdit::searchIsEmpty, chatListView_, &ChatListView::setMainModel);
    
    connect(chatListView_, &ChatListView::chatSelected, searchLineEdit_, &SearchLineEdit::clear);
    
    connect(chatListView_, &ChatListView::chatSelected, this, &ChatListSide::selectionWasChanged);
    
    connect(chatListView_, &ChatListView::foundUserSelected, this, &ChatListSide::selectionWasChanged);
    
    connect(chatListView_, &ChatListView::newChatItemAdded, this, &ChatListSide::newChatItemAdded);

    connect(chatListView_, &ChatListView::localSearchFinished, searchLineEdit_, &SearchLineEdit::startSearchOnServer);
}

void ChatListSide::clearChatSelection()
{
    const auto prevIndex = chatListView_->currentIndex();
    chatListView_->clearSelection();
    chatListView_->setCurrentIndex(QModelIndex{});
    chatListView_->update(prevIndex);
}

void ChatListSide::setToMainModelAndSelectChat(int chatId)
{
    chatListView_->setMainModelSelected(chatId);
}

void ChatListSide::setupUi()
{
    drawerButton_ = new IconButton{QPixmap{":/images/drawer_button.png"}};
    connect(drawerButton_, &IconButton::clicked, this, &ChatListSide::drawerRequested);

    searchLineEdit_ = new SearchLineEdit;
    searchLineEdit_->setPlaceholderText(tr("Search"));

    QHBoxLayout *hLayout = new QHBoxLayout;
    const int m = 8;
    hLayout->setContentsMargins(m, m, m, m);
    hLayout->setSpacing(m);
    hLayout->addWidget(drawerButton_);
    hLayout->addWidget(searchLineEdit_);

    Widget *head = new Widget;
    head->setLayout(hLayout);

    chatListView_ = new ChatListView;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(head);
    vLayout->addWidget(chatListView_);

    setLayout(vLayout);

    setBackgroundColor(Colors.value(colornames::backgroundLighterHelper1));
    head->setBackgroundColor(palette().window().color());
}
