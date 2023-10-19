#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include "messagemodelitem.h"

#include <sql_common/data_structures/message.h>

#include <QString>
#include <QDateTime>
#include <QRect>
#include <QFont>

#include <memory>

class MessageItem;

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
        TextLines,
        SplittedText,
        HasSelection,
        Selection,

        MessageData,

        TextFont,
        TimeFont,

        BackgroundRect,
        TextRect,
        TimeRect,
        IsReadPos,
    };

    explicit MessageItem();

    int         messageId()    const;
    int         senderId()     const;
    QString     text()         const;
    QString     splittedText() const;
    QDateTime   dateTime()     const;
    bool        isRead()       const;
    bool        isEdited()     const;
    QStringList textLines()    const;
    bool        hasSelection() const;
    QString     selection()    const;

    QFont textFont() const;
    QFont timeFont() const;

    QRect  backgroundRect() const;
    QRect  textRect()       const;
    QRect  timeRect()       const;
    QPoint isReadPos()      const;

    void setData(int role, const QVariant &data) override;

    static MessageItemPtr fromMessage(const Message &message);

protected:
    QVariant dataImp(int role) const override;

private:
    void setTextLines(const QString &text);

    void setMessageId(int messageId);
    void setSenderId(int senderId);
    void setText(const QString &text);
    void setDateTime(const QDateTime &dateTime);
    void setIsRead(bool isRead);
    void setIsEdited(bool isEdited);


    QRect getTextBRect(const QString &t, const QFont &f) const;
    bool senderIsMe() const;
    int lastLineFullWidth(const QRect &lastLineRect, const QRect &timeRect) const;

    void calculateDrawData();
    QRect getBackgroundRect() const;
    QRect getTextRect() const;
    QRect getTimeRect() const;
    QPoint getIsReadPos() const;

private:
    Message message_;

    bool hasSelection_ = false;
    QString selection_;

    QString splittedText_;
    QStringList textLines_;

    struct DrawData
    {
        QFont textFont;
        QFont timeFont;

        QRect backgroundRect;
        QRect textRect; // text will be drawn in that rect
        QRect timeRect; // text will be drawn in that rect

        QPoint isReadPoint;
    };

    DrawData drawData_;
};

#endif // MESSAGEITEM_H
