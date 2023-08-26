#include "ui/mv/messageitem.h"

#include <sql_common/data_structures/message.h>

#include <QTextOption>
#include <QTextDocument>
#include <QTextBlock>
#include <QVariant>
#include <QDebug>

QTextOption textOption()
{
    QTextOption to;
    to.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    to.setAlignment(Qt::AlignLeft);
    return to;
}

MessageItem::MessageItem()
    : MessageModelItem{Type::MessageItem}
{
}

int MessageItem::messageId() const
{
    return messageId_;
}

void MessageItem::setMessageId(int newMessageId)
{
    messageId_ = newMessageId;
}


int MessageItem::senderId() const
{
    return senderId_;
}

void MessageItem::setSenderId(int newSenderId)
{
    senderId_ = newSenderId;
}

QString MessageItem::text() const
{
    return text_;
}

void MessageItem::setText(const QString &newText)
{
    text_ = newText;
    setSplittedText();
}

QDateTime MessageItem::dateTime() const
{
    return dateTime_;
}

void MessageItem::setDateTime(const QDateTime &newDateTime)
{
    dateTime_ = newDateTime;
}

MessageItemPtr MessageItem::fromMessage(const Message &message)
{
    MessageItemPtr messageItem{new MessageItem};

    messageItem->setMessageId(message.id());
    messageItem->setSenderId(message.senderId());
    messageItem->setText(message.text());
    messageItem->setDateTime(message.createdAt());
    messageItem->setIsRead(message.isRead());
    messageItem->setIsEdited(message.isEdited());

    return messageItem;
}

QVariant MessageItem::dataImp(int role) const
{
    switch (static_cast<Roles>(role)) {
    case Roles::MessageId:    return messageId_;    break;
    case Roles::SenderId:     return senderId_;     break;
    case Roles::Text:         return text_;         break;
    case Roles::DateTime:     return dateTime_;     break;
    case Roles::IsRead:       return isRead_;       break;
    case Roles::IsEdited:     return isEdited_;     break;
    case Roles::SplittedText: return splittedText_; break;
    }
    return QVariant{};
}

void MessageItem::setSplittedText()
{
    splittedText_.clear();

    QTextDocument doc;
    doc.setPlainText(text_);
    doc.setDefaultTextOption(textOption());
    doc.setTextWidth(MaxContentWidth);

    doc.documentLayout();

    QTextBlock textBlock = doc.begin();
    while(textBlock.isValid()) {
        QString blockText = textBlock.text();

        if(!textBlock.layout())
            continue;

        for(int i = 0; i != textBlock.layout()->lineCount(); ++i) {
            QTextLine line = textBlock.layout()->lineAt(i);
            splittedText_.append(blockText.mid(line.textStart(), line.textLength()));
        }

        textBlock = textBlock.next();
    }
}

bool MessageItem::isEdited() const
{
    return isEdited_;
}

void MessageItem::setIsEdited(bool newIsEdited)
{
    isEdited_ = newIsEdited;
}

bool MessageItem::isRead() const
{
    return isRead_;
}

void MessageItem::setIsRead(bool newIsRead)
{
    isRead_ = newIsRead;
}

void MessageItem::setData(int role, const QVariant &data)
{
    switch (static_cast<Roles>(role)) {
    case Roles::MessageId: setMessageId(data.toInt());     break;
    case Roles::SenderId:  setSenderId(data.toInt());      break;
    case Roles::Text:      setText(data.toString());       break;
    case Roles::DateTime:  setDateTime(data.toDateTime()); break;
    case Roles::IsRead:    setIsRead(data.toBool());       break;
    case Roles::IsEdited:  setIsEdited(data.toBool());     break;
    }
}
