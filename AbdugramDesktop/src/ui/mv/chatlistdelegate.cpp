#include "ui/mv/chatlistdelegate.h"
#include "ui/mv/chatitem.h"
#include "ui/mv/founduseritem.h"

#include "ui/colorrepository.h"

#include <QPainter>
#include <QDebug>

const QMargins AvatarMargins_      = QMargins{5, 10, 0, 10};
const QSize    AvatarSize_         = QSize{45, 45};
const QMargins ChatNameMargins_    = QMargins{10, 8, 0, 0};
const QMargins LastMessageMargins_ = QMargins{0, 0, 0, 5};
const QMargins MessageDateMargins_ = QMargins{5, 8, 5, 0};

const int SeparatorThin_ = 1;

inline QColor chatNameColor()
{
    return Colors.value(colornames::mainLabelColor);
}

inline QColor lastMessageColor()
{
    return Colors.value(colornames::secondaryLabelColor);
}

inline QColor messageDateColor()
{
    return Colors.value(colornames::secondaryLabelColor);
}

inline QColor highlightColor()
{
    return Colors.value(colornames::decorationColor);
}

inline QFont boldFont(QFont f)
{
    f.setBold(true);
    return f;
}

ChatListDelegate::ChatListDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void ChatListDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    const int type = index.data(ChatModelItem::Roles::Type).toInt();
    switch (type) {
    case ChatModelItem::Type::ChatItem: drawChatItem(painter, option, index);           break;
    case ChatModelItem::Type::FoundUserItem: drawFoundUserItem(painter, option, index); break;
    case ChatModelItem::Type::LineSeparator: drawLineSeparator(painter, option, index);     break;
    }

    painter->restore();
}

QSize ChatListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    const int type = index.data(ChatModelItem::Type).toInt();
    switch (type) {
    case ChatModelItem::Type::ChatItem:
    case ChatModelItem::Type::FoundUserItem:
        return chatItemSizeHint(option, index);
        break;
    case ChatModelItem::Type::LineSeparator:
        return lineSeparatorSizeHint(option, index);
    }

    return QSize{};
}

void ChatListDelegate::setPainterOrigin(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int dx = 0;
    const int dy = option.rect.top();
    painter->translate(dx, dy);
}

void ChatListDelegate::drawChatItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    drawBackground(painter, option, index);

    setPainterOrigin(painter, option, index);

    drawChatPicture(painter, option, index);
    drawChatName(painter, option, index);
    drawLastMessage(painter, option, index);
    drawMessageDate(painter, option, index);

    painter->restore();
}

void ChatListDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    if (!(option.state & QStyle::State_Selected))
        return;

    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(highlightColor());
    painter->drawRect(option.rect);

    painter->restore();
}

void ChatListDelegate::drawChatPicture(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const int x = AvatarMargins_.left();
    const int y = AvatarMargins_.top();

    const QPixmap avatar = QPixmap{":/images/avatar.png"}.scaled(AvatarSize_);
    painter->drawPixmap(x, y, avatar);

    painter->restore();
}

void ChatListDelegate::drawChatName(QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    painter->save();
    painter->setPen(QPen{chatNameColor()});
    painter->setFont(boldFont(option.font));

    const int x = AvatarMargins_.left() + AvatarSize_.width() + ChatNameMargins_.left();
    const int y = ChatNameMargins_.top() + painter->fontMetrics().height();

    const QString chatName = index.data(ChatItem::Roles::ChatName).toString();

    const QDateTime messageDate = index.data(ChatItem::Roles::MessageDate).toDateTime();
    const QString   stringDate  = dateTimeToString(messageDate);

    const int width = option.rect.width() - x - option.fontMetrics.horizontalAdvance(stringDate)
                      - MessageDateMargins_.left() - MessageDateMargins_.right();

    const QString elidedName = painter->fontMetrics().elidedText(chatName, Qt::ElideRight, width);
    painter->drawText(x, y, elidedName);

    painter->restore();
}

void ChatListDelegate::drawLastMessage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    if (option.state & QStyle::State_Selected)
        painter->setPen(QPen{chatNameColor()});
    else
        painter->setPen(QPen{lastMessageColor()});

    const int x = AvatarMargins_.left() + AvatarSize_.width() + ChatNameMargins_.left();
    const int y = AvatarMargins_.top() + AvatarSize_.height() - LastMessageMargins_.bottom();

    const QString lastMessage = index.data(ChatItem::Roles::LastMessage).toString();
    const int width = option.rect.width() - x - MessageDateMargins_.right();
    const QString elidedMessage = option.fontMetrics.elidedText(lastMessage, Qt::ElideRight, width);
    painter->drawText(x, y, elidedMessage);

    painter->restore();
}

void ChatListDelegate::drawMessageDate(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    if (option.state & QStyle::State_Selected)
        painter->setPen(QPen{chatNameColor()});
    else
        painter->setPen(QPen{messageDateColor()});

    int       x = option.rect.right() - MessageDateMargins_.right();
    const int y = MessageDateMargins_.top() + option.fontMetrics.height();

    const QDateTime messageDate = index.data(ChatItem::Roles::MessageDate).toDateTime();
    const QString   stringDate  = dateTimeToString(messageDate);
    x -= option.fontMetrics.horizontalAdvance(stringDate);

    painter->drawText(x, y, stringDate);

    painter->restore();
}

void ChatListDelegate::drawFoundUserItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    drawBackground(painter, option, index);

    setPainterOrigin(painter, option, index);

    drawUsername(painter, option, index);
    drawAvatar(painter, option, index);

    painter->restore();
}

void ChatListDelegate::drawUsername(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setPen(QPen{chatNameColor()});
    painter->setFont(boldFont(option.font));

    const int x = AvatarMargins_.left() + AvatarSize_.width() + ChatNameMargins_.left();
    const int y = ChatNameMargins_.top() + painter->fontMetrics().height();

    const QString chatName = index.data(FoundUserItem::Roles::Username).toString();
    const int width = option.rect.width() - x - MessageDateMargins_.right();
    const QString elidedName = option.fontMetrics.elidedText(chatName, Qt::ElideRight, width);
    painter->drawText(x, y, elidedName);

    painter->restore();
}

void ChatListDelegate::drawAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const int x = AvatarMargins_.left();
    const int y = AvatarMargins_.top();

    const QPixmap avatar = QPixmap{":/images/avatar.png"}.scaled(AvatarSize_);
    painter->drawPixmap(x, y, avatar);

    painter->restore();
}

void ChatListDelegate::drawLineSeparator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const int x = AvatarMargins_.left() + AvatarSize_.width() + ChatNameMargins_.left();
    const int y = option.rect.y();

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawRect(QRect{QPoint{x, y}, option.rect.bottomRight()});;

    painter->restore();
}

QSize ChatListDelegate::chatItemSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize{option.rect.width(), 65};
}

QSize ChatListDelegate::lineSeparatorSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize{option.rect.width(), 1};
}

QString ChatListDelegate::dateTimeToString(const QDateTime &dateTime) const
{
    const int daysToCurrentDay = dateTime.daysTo(QDateTime::currentDateTime());
    if (daysToCurrentDay == 0) {
        return dateTime.toString("hh:mm");
    } else if (daysToCurrentDay < 7) {
        return dateTime.toString("ddd");
    }

    return dateTime.toString("dd.MM.yy");
}
