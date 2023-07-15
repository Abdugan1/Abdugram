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
        SenderId = static_cast<int>(MessageModelItem::Roles::UserRole) + 1,
        Text,
        DateTime
    };

    explicit MessageItem();

    int senderId() const;
    void setSenderId(int newSenderId);

    QString text() const;
    void setText(const QString &newText);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    static MessageItemPtr fromMessage(const Message &message);

protected:
    QVariant dataImp(int role) const override;

private:
    int senderId_ = -1;
    QString text_;
    QDateTime dateTime_;
};

#endif // MESSAGEITEM_H
