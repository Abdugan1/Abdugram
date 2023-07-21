#ifndef CHATITEM_H
#define CHATITEM_H

#include "chatmodelitem.h"

#include <QString>
#include <QDateTime>
#include <QUrl>

#include <memory>

#include <sql_common/data_structures/chat.h>

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
    };

    explicit ChatItem();

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


protected:
    QVariant dataImp(int role) const override;

private:
    QUrl pictureUrl_;
    QString chatName_;
    QString lastMessage_;
    QDateTime messageDate_;

    Chat::Type chatType_ = Chat::Type::Private;
    int chatId_ = -1;
};

#endif // CHATITEM_H
