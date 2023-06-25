#include "ui/sidepanel.h"
#include "ui/imagebutton.h"
#include "ui/searchlineedit.h"

#include "ui/mv/chatlistview.h"

#include <sql_common/data_structures/chat.h>

#include <sql_client/databaseclient.h>

#include <QBoxLayout>
#include <QDebug>

SidePanel::SidePanel(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(searchLineEdit_, &SearchLineEdit::searchIsEmpty, chatListView_, &ChatListView::setMainModel);

    connect(chatListView_, &ChatListView::selectionWasChanged, this, &SidePanel::selectionWasChanged);

    //
    connect(database(), &DatabaseClient::chatAdded, this, &SidePanel::addNewChatToView);
}

void SidePanel::addNewChatToView(const Chat &chat)
{    
    ChatItemPtr chatItem{new ChatItem};
    chatItem->setChatId(chat.id());
    chatItem->setChatName(chat.name());
    chatItem->setChatType(chat.type());

    chatListView_->addNewChatItemToMainModel(chatItem);

    emit newChatItemAdded(chatItem);
}

void SidePanel::setupUi()
{
    openDrawer_ = new ImageButton{QPixmap{":/images/drawer_button.png"}};
    searchLineEdit_ = new SearchLineEdit;
    searchLineEdit_->setPlaceholderText(tr("Search"));

    QHBoxLayout *hLayout = new QHBoxLayout;
    const int m = 8;
    hLayout->setContentsMargins(m, m, m, m);
    hLayout->setSpacing(m);
    hLayout->addWidget(openDrawer_);
    hLayout->addWidget(searchLineEdit_);

    chatListView_ = new ChatListView;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(chatListView_);

    setLayout(vLayout);
}
