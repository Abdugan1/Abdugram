#include "sidepanel.h"
#include "imagebutton.h"
#include "searchlineedit.h"
#include "mv/chatlistview.h"

#include "net/networkhandler.h"

#include <sql_common/data_structures/chat.h>

#include <sql_client/chatstable.h>

#include <QBoxLayout>

SidePanel::SidePanel(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(searchLineEdit_, &SearchLineEdit::searchIsEmpty, chatListView_, &ChatListView::setMainModel);

    connect(chatListView_, &ChatListView::selectionWasChanged, this, &SidePanel::selectionWasChanged);


    //
    connect(networkHandler(), &NetworkHandler::newChatAdded, this, [this](int chatId) {
        Chat chat = ChatsTable::getChatById(chatId);
        ChatItemPtr chatItem{new ChatItem};
        chatItem->setChatId(chat.id());
        chatItem->setChatName(chat.name());
        chatItem->setChatType(chat.type());

        chatListView_->addNewChatItemToMainModel(chatItem);

        emit newChatItemAdded(chatItem);
    });
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
