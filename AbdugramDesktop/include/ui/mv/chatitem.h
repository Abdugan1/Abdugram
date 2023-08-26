#ifndef CHATITEM_H
#define CHATITEM_H

#include "chatmodelitem.h"

#include <QString>
#include <QDateTime>
#include <QUrl>

#include <memory>

#include <sql_client/data_structures/chatitem.h>

class ChatItem;

using ChatItemPtr = std::shared_ptr<ChatItem>;

class ChatItem : public ChatModelItem
{
public:
    enum Roles {
        ChatId = ChatModelItem::Roles::UserRole + 1,
        ChatName,
        PictureUrl,
        LastMessage,
        MessageDate,
        ChatType,
        UnreadMessageCount
    };

    explicit ChatItem();

    int chatId() const;
    void setChatId(int newChatId);

    QString chatName() const;
    void setChatName(const QString &newChatName);

    QUrl pictureUrl() const;
    void setPictureName(const QUrl &newPictureUrl);

    QString lastMessage() const;
    void setLastMessage(const QString &newLastMessage);

    QDateTime messageDate() const;
    void setMessageDate(const QDateTime &newMessageDate);

    Chat::Type chatType() const;
    void setChatType(Chat::Type newChatType);

    int unreadMessageCount() const;
    void setUnreadMessageCount(int newUnreadMessageCount);

    static ChatItemPtr fromChatViewItem(const ChatViewItem &newChatView);

protected:
    QVariant dataImp(int role) const override;

private:
    ChatViewItem chatView_;
};

#endif // CHATITEM_H
