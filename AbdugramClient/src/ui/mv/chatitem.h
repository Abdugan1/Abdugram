#ifndef CHATITEM_H
#define CHATITEM_H

#include <QString>
#include <QDateTime>
#include <QUrl>

#include <sql_common/data_structures/chat.h>

class ChatItem
{
public:
    explicit ChatItem();

    QUrl avatar() const;
    void setAvatar(const QUrl &newAvatar);

    QString chatName() const;
    void setChatName(const QString &newChatName);

    QString lastMessage() const;
    void setLastMessage(const QString &newLastMessage);

    QDateTime messageDate() const;
    void setMessageDate(const QDateTime &newMessageDate);

    Chat::Type chatType() const;
    void setChatType(Chat::Type newChatType);

    int id() const;
    void setId(int newId);

    int userId() const;
    void setUserId(int newUserId);

private:
    QUrl avatar_;
    QString chatName_;
    QString lastMessage_;
    QDateTime messageDate_;

    Chat::Type chatType_ = Chat::Type::Private;
    int id_ = -1;
    int userId_ = -1;
};

#endif // CHATITEM_H
