#ifndef CHATITEM_H
#define CHATITEM_H

#include <QString>
#include <QDateTime>
#include <QUrl>

#include <memory>

#include <sql_common/data_structures/chat.h>

class ChatItem;

using ChatItemPtr = std::shared_ptr<ChatItem>;

class ChatItem
{
public:
    explicit ChatItem();
    virtual ~ChatItem() = default;

    QUrl pictureUrl() const;
    void setPictureUrl(const QUrl &newPictureUrl);

    QString chatName() const;
    void setChatName(const QString &newChatName);

    QString lastMessage() const;
    void setLastMessage(const QString &newLastMessage);

    QDateTime messageDate() const;
    void setMessageDate(const QDateTime &newMessageDate);

    Chat::Type chatType() const;
    void setChatType(Chat::Type newChatType);

    int chatId() const;
    void setChatId(int newId);

private:
    QUrl pictureUrl_;
    QString chatName_;
    QString lastMessage_;
    QDateTime messageDate_;

    Chat::Type chatType_ = Chat::Type::Private;
    int chatId_ = -1;
};

#endif // CHATITEM_H
