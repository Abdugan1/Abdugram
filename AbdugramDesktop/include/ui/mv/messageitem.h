#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include "messagemodelitem.h"

#include <QString>
#include <QDateTime>

#include <memory>

class MessageItem;
class Message;

using MessageItemPtr = std::shared_ptr<MessageItem>;

class MessageItem : public MessageModelItem
{
public:
    enum Roles {
        MessageId = static_cast<int>(MessageModelItem::Roles::UserRole) + 1,
        SenderId,
        Text,
        DateTime,
        IsRead,
        IsEdited
    };

    explicit MessageItem();

    int messageId() const;
    void setMessageId(int newMessageId);

    int senderId() const;
    void setSenderId(int newSenderId);

    QString text() const;
    void setText(const QString &newText);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    bool isRead() const;
    void setIsRead(bool newIsRead);

    bool isEdited() const;
    void setIsEdited(bool newIsEdited);

    void setData(int role, const QVariant &data) override;

    static MessageItemPtr fromMessage(const Message &message);

protected:
    QVariant dataImp(int role) const override;

private:
    int messageId_ = -1;
    int senderId_ = -1;
    QString text_;
    QDateTime dateTime_;
    bool isRead_ = false;
    bool isEdited_ = false;
};

#endif // MESSAGEITEM_H
