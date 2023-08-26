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
    enum {
        MaxContentWidth = 400,

        BackgroundLeftPadding   = 17,
        BackgroundTopPadding    = 10,
        BackgroundRightPadding  = 17,
        BackgroundBottomPadding = 10,

        TimeHSpacing = 7,
        TimeVSpacing = 7,

        IsReadWidth = 15,
    };

    enum Roles {
        MessageId = static_cast<int>(MessageModelItem::Roles::UserRole) + 1,
        SenderId,
        Text,
        DateTime,
        IsRead,
        IsEdited,

        SplittedText,
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
    void setSplittedText();

private:
    int messageId_ = -1;
    int senderId_ = -1;
    QString text_;
    QDateTime dateTime_;
    bool isRead_ = false;
    bool isEdited_ = false;

    QStringList splittedText_;
};

#endif // MESSAGEITEM_H
