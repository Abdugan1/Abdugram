#include "chatlistview.h"
#include "chatlistmodel.h"
#include "chatlistdelegate.h"

#include "net/networkhandler.h"

ChatListView::ChatListView(QWidget *parent)
    : QListView{parent}
    , mainModel_{new ChatListModel{this}}
    , tempModel_{new ChatListModel{this}}
    , delegate_{new ChatListDelegate{this}}
{
    connect(this, &ChatListView::chatNameColorChanged, this, [this]() {
        delegate_->setChatNameColor(chatNameColor_);
    });
    connect(this, &ChatListView::lastMessageColorChanged, this, [this]() {
        delegate_->setLastMessageColor(lastMessageColor_);
    });
    connect(this, &ChatListView::messageDateColorChanged, this, [this]() {
        delegate_->setMessageDateColor(messageDateColor_);
    });
    connect(this, &ChatListView::highlightColorChanged, this, [this]() {
        delegate_->setHighlightColor(highlightColor_);
    });

    connect(networkHandler(), &NetworkHandler::searchResult, this, &ChatListView::setTemporaryModel);

    setModel(mainModel_);
    setItemDelegate(delegate_);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setVerticalScrollMode(QListView::ScrollPerPixel);

    setContentsMargins(0, 0, 0, 0);
}

QColor ChatListView::chatNameColor() const
{
    return chatNameColor_;
}

void ChatListView::setChatNameColor(const QColor &newChatNameColor)
{
    if (chatNameColor_ == newChatNameColor)
        return;
    chatNameColor_ = newChatNameColor;
    emit chatNameColorChanged();
}

QColor ChatListView::lastMessageColor() const
{
    return lastMessageColor_;
}

void ChatListView::setLastMessageColor(const QColor &newLastMessageColor)
{
    if (lastMessageColor_ == newLastMessageColor)
        return;
    lastMessageColor_ = newLastMessageColor;
    emit lastMessageColorChanged();
}

QColor ChatListView::messageDateColor() const
{
    return messageDateColor_;
}

void ChatListView::setMessageDateColor(const QColor &newMessageDateColor)
{
    if (messageDateColor_ == newMessageDateColor)
        return;
    messageDateColor_ = newMessageDateColor;
    emit messageDateColorChanged();
}

QColor ChatListView::highlightColor() const
{
    return highlightColor_;
}

void ChatListView::setHighlightColor(const QColor &newHighlightColor)
{
    if (highlightColor_ == newHighlightColor)
        return;
    highlightColor_ = newHighlightColor;
    emit highlightColorChanged();
}

void ChatListView::setTemporaryModel(const QList<User> &foundUserList)
{
    tempModel_->clear();

}
