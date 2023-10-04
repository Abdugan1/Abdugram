#include "ui/mv/messageitem.h"

#include "net/networkhandler.h"

#include <sql_common/data_structures/message.h>

#include <QTextOption>
#include <QTextDocument>
#include <QTextBlock>
#include <QFontMetrics>
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
    return message_.id();
}

int MessageItem::senderId() const
{
    return message_.senderId();
}

QString MessageItem::text() const
{
    return message_.text();
}

QString MessageItem::splittedText() const
{
    return splittedText_;
}

QDateTime MessageItem::dateTime() const
{
    return message_.createdAt();
}

bool MessageItem::isEdited() const
{
    return message_.isEdited();
}

bool MessageItem::isRead() const
{
    return message_.isRead();
}

QStringList MessageItem::textLines() const
{
    return textLines_;
}

QRect MessageItem::backgroundRect() const
{
    return drawData_.backgroundRect;
}

QRect MessageItem::textRect() const
{
    return drawData_.textRect;
}

QRect MessageItem::timeRect() const
{
    return drawData_.timeRect;
}

QPoint MessageItem::isReadPos() const
{
    return drawData_.isReadPoint;
}

MessageItemPtr MessageItem::fromMessage(const Message &message)
{
    MessageItemPtr messageItem{new MessageItem};

    messageItem->message_ = message;
    messageItem->setTextLines(message.text());
    messageItem->splittedText_ = messageItem->textLines_.join('\n');

    messageItem->calculateDrawData();

    return messageItem;
}

QVariant MessageItem::dataImp(int role) const
{
    switch (static_cast<Roles>(role)) {
    case Roles::MessageId:    return messageId();    break;
    case Roles::SenderId:     return senderId();     break;
    case Roles::Text:         return text();         break;
    case Roles::SplittedText: return splittedText(); break;
    case Roles::DateTime:     return dateTime();     break;
    case Roles::IsRead:       return isRead();       break;
    case Roles::IsEdited:     return isEdited();     break;
    case Roles::TextLines:    return textLines(); break;

    case Roles::TextFont:       return drawData_.textFont;       break;
    case Roles::TimeFont:       return drawData_.timeFont;       break;
    case Roles::BackgroundRect: return drawData_.backgroundRect; break;
    case Roles::TextRect:       return drawData_.textRect;       break;
    case Roles::TimeRect:       return drawData_.timeRect;       break;
    case Roles::IsReadPos:      return drawData_.isReadPoint;    break;
    default:
        break;
    }
    return QVariant{};
}

void MessageItem::setData(int role, const QVariant &data)
{
    switch (static_cast<Roles>(role)) {
    case Roles::MessageData:
        *this = *fromMessage(data.value<Message>());
        break;
    default:
        break;
    }
}

void MessageItem::setTextLines(const QString &text)
{
    textLines_.clear();

    QTextDocument doc;
    doc.setPlainText(text);
    doc.setDefaultTextOption(textOption());
    doc.setTextWidth(MaxContentWidth);

    doc.documentLayout(); // Must have thing! It seems it creates layout

    QTextBlock textBlock = doc.begin();
    while(textBlock.isValid()) {
        QString blockText = textBlock.text();

        if(!textBlock.layout())
            continue;

        for(int i = 0; i != textBlock.layout()->lineCount(); ++i) {
            QTextLine line = textBlock.layout()->lineAt(i);
            textLines_.append(blockText.mid(line.textStart(), line.textLength()));
        }

        textBlock = textBlock.next();
    }
}

void MessageItem::setMessageId(int messageId)
{
    message_.setId(messageId);
}

void MessageItem::setSenderId(int senderId)
{
    message_.setSenderId(senderId);
}

void MessageItem::setText(const QString &text)
{
    setTextLines(text);
    message_.setText(textLines_.join('\n'));
}

void MessageItem::setDateTime(const QDateTime &dateTime)
{
    message_.setCreatedAt(dateTime);
}

void MessageItem::setIsRead(bool isRead)
{
    message_.setIsRead(isRead);
}

void MessageItem::setIsEdited(bool isEdited)
{
    message_.setIsEdited(isEdited);
}

QRect MessageItem::getTextBRect(const QString &t, const QFont &f) const
{
    return QFontMetrics{f}.boundingRect(0, 0, MaxContentWidth, INT_MAX, Qt::AlignLeft, t);
}

bool MessageItem::senderIsMe() const
{
    return senderId() == networkHandler()->userId();
}

int MessageItem::lastLineFullWidth(const QRect &lastLineRect, const QRect &timeRect) const
{
    return lastLineRect.width() + TimeHSpacing + timeRect.width() + (senderIsMe() ? IsReadWidth : 0);
}

void MessageItem::calculateDrawData()
{
    QFont textFont;
    textFont.setPointSize(11);

    QFont timeFont;
    timeFont.setPointSizeF(textFont.pointSizeF() - 0.5);

    drawData_.textFont = textFont;
    drawData_.timeFont = timeFont;

    drawData_.backgroundRect = getBackgroundRect();
    drawData_.textRect       = getTextRect();
    drawData_.timeRect       = getTimeRect();
    drawData_.isReadPoint    = getIsReadPos();
}

QRect MessageItem::getBackgroundRect() const
{
    QRect backgroundRect;

    const QRect textRect = getTextBRect(splittedText(), drawData_.textFont);

    const QString time     = dateTime().toString("hh:mm");
    const QRect   timeRect = getTextBRect(time, drawData_.timeFont);
    
    const QRect lastLineRect = getTextBRect(textLines_.constLast(), drawData_.textFont);

    backgroundRect = textRect;

    if (lastLineFullWidth(lastLineRect, timeRect) <= MaxContentWidth) {
        backgroundRect.setWidth(backgroundRect.width() + TimeHSpacing + timeRect.width());
    } else {
        backgroundRect.setBottom(backgroundRect.bottom() + timeRect.height());
    }
    if (senderIsMe())
        backgroundRect.setWidth(backgroundRect.width() + IsReadWidth);

    backgroundRect = QRect{0, 0,
                           backgroundRect.width()  + BackgroundLeftPadding + BackgroundRightPadding,
                           backgroundRect.height() + BackgroundTopPadding  + BackgroundBottomPadding};


    return backgroundRect;
}

QRect MessageItem::getTextRect() const
{
    QRect textRect = getTextBRect(splittedText(), drawData_.textFont);
    textRect.moveTopLeft(QPoint{BackgroundLeftPadding, BackgroundTopPadding});
    return textRect;
}

QRect MessageItem::getTimeRect() const
{
    const QString time = dateTime().toString("hh:mm");
    QRect timeRect = getTextBRect(time, drawData_.timeFont);
    
    auto lastLineBoundingRect = getTextBRect(textLines_.constLast(), drawData_.textFont);
    lastLineBoundingRect.moveTop(BackgroundTopPadding + drawData_.textRect.height() - lastLineBoundingRect.height());

    timeRect.moveRight(drawData_.backgroundRect.right() - BackgroundRightPadding - (senderIsMe() ? IsReadWidth : 0));

    if (lastLineFullWidth(lastLineBoundingRect, timeRect) <= MaxContentWidth)
        timeRect.moveBottom(lastLineBoundingRect.bottom() + TimeVSpacing);
    else
        timeRect.moveBottom(lastLineBoundingRect.bottom() + timeRect.height());

    return timeRect;
}

QPoint MessageItem::getIsReadPos() const
{
    return QPoint{drawData_.backgroundRect.right()  - BackgroundRightPadding,
                  drawData_.backgroundRect.bottom() - BackgroundBottomPadding};
}
