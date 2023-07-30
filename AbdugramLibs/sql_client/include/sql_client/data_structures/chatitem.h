#ifndef CHATVIEWITEM_H
#define CHATVIEWITEM_H

#include "../SqlClient_global.h"

#include <QString>
#include <QDateTime>
#include <QUrl>

#include <memory>

#include <sql_common/data_structures/chat.h>

class SQLCLIENT_EXPORT ChatViewItem
{
public:
    explicit ChatViewItem();

    int chatId() const;
    void setChatId(int newId);

    QString chatName() const;
    void setChatName(const QString &newChatName);

    QUrl pictureUrl() const;
    void setPictureUrl(const QUrl &newPictureUrl);

    QString lastMessage() const;
    void setLastMessage(const QString &newLastMessage);

    QDateTime messageDate() const;
    void setMessageDate(const QDateTime &newMessageDate);

    Chat::Type chatType() const;
    void setChatType(Chat::Type newChatType);

    static ChatViewItem fromSqlRecord(const QSqlRecord &record);

    SQLCOMMON_EXPORT friend QDataStream &operator<<(QDataStream &out, const ChatViewItem &chatItem);
    SQLCOMMON_EXPORT friend QDataStream &operator>>(QDataStream &in, ChatViewItem &chatItem);

private:
    int chatId_ = -1;
    QUrl pictureUrl_;
    QString chatName_;
    QString lastMessage_;
    QDateTime messageDate_;

    Chat::Type chatType_ = Chat::Type::Private;
};

#endif // CHATVIEWITEM_H
