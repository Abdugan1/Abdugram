#include "ui/mv/chatlistdelegate.h"
#include "ui/mv/chatitem.h"
#include "ui/mv/founduseritem.h"
#include "ui/mv/sectionseparator.h"

#include "ui/components/colorrepository.h"

#include <QPainter>
#include <QDebug>

const QMargins AvatarMargins      = QMargins{7, 10, 0, 10};
const QSize    AvatarSize         = QSize{45, 45};
const QMargins ChatNameMargins    = QMargins{10, 8, 0, 0};
const QMargins LastMessageMargins = QMargins{0, 0, 0, 5};
const QMargins MessageDateMargins = QMargins{5, 8, 5, 0};
const QMargins SectionNameMargins = QMargins{10, 0, 0, 0};

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

inline QColor sectionBackgroundColor()
{
    return Colors.value(colornames::backgroundLighterHelper3);
}

inline QColor sectionNameColor()
{
    return Colors.value(colornames::secondaryLabelColor);
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
    case ChatModelItem::Type::ChatItem:
        drawChatItem(painter, option, index);
        break;
    case ChatModelItem::Type::FoundUserItem:
        drawFoundUserItem(painter, option, index);
        break;
    case ChatModelItem::Type::SectionSeparator:
        drawSectionSeparator(painter, option, index);
        break;
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
    case ChatModelItem::Type::SectionSeparator:
        return sectionSeparatorSizeHint(option, index);
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

    painter->save();

    if (option.state & QStyle::State_Selected) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(highlightColor());
        painter->drawRect(option.rect);
    } else if (option.state & QStyle::State_MouseOver) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor{255, 255, 255, 25});
        painter->drawRect(option.rect);
    }

    painter->restore();
}

void ChatListDelegate::drawChatPicture(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const int x = AvatarMargins.left();
    const int y = AvatarMargins.top();

    const QPixmap avatar = QPixmap{":/images/avatar.png"}.scaled(AvatarSize);
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

    const int x = AvatarMargins.left() + AvatarSize.width() + ChatNameMargins.left();
    const int y = ChatNameMargins.top() + painter->fontMetrics().height();
    
    const QString chatName = index.data(ChatItem::Roles::ChatName).toString();
    
    const QDateTime messageDate = index.data(ChatItem::Roles::MessageDate).toDateTime();
    const QString   stringDate  = dateTimeToString(messageDate);

    const int width = option.rect.width() - x - option.fontMetrics.horizontalAdvance(stringDate)
                      - MessageDateMargins.left() - MessageDateMargins.right();

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

    const int x = AvatarMargins.left() + AvatarSize.width() + ChatNameMargins.left();
    const int y = AvatarMargins.top() + AvatarSize.height() - LastMessageMargins.bottom();
    
    const QString lastMessage = index.data(ChatItem::Roles::LastMessage).toString();
    const int width = option.rect.width() - x - MessageDateMargins.right();
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

    int       x = option.rect.right() - MessageDateMargins.right();
    const int y = MessageDateMargins.top() + option.fontMetrics.height();
    
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

    const int x = AvatarMargins.left() + AvatarSize.width() + ChatNameMargins.left();
    const int y = ChatNameMargins.top() + painter->fontMetrics().height();

    const QString chatName = index.data(FoundUserItem::Roles::Username).toString();
    const int width = option.rect.width() - x - MessageDateMargins.right();
    const QString elidedName = option.fontMetrics.elidedText(chatName, Qt::ElideRight, width);
    painter->drawText(x, y, elidedName);

    painter->restore();
}

void ChatListDelegate::drawAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const int x = AvatarMargins.left();
    const int y = AvatarMargins.top();

    const QPixmap avatar = QPixmap{":/images/avatar.png"}.scaled(AvatarSize);
    painter->drawPixmap(x, y, avatar);

    painter->restore();
}

void ChatListDelegate::drawSectionSeparator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    drawSectionBackground(painter, option, index);

    setPainterOrigin(painter, option, index);
    drawSectionName(painter, option, index);

    painter->restore();
}

void ChatListDelegate::drawSectionBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(sectionBackgroundColor());
    painter->drawRect(option.rect);

    painter->restore();
}

void ChatListDelegate::drawSectionName(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const int x = SectionNameMargins.left();
    const int y = option.rect.height() / 2 + option.fontMetrics.ascent() / 2;

    const auto sectionName = index.data(SectionSeparator::SectionName).toString();

    painter->setPen(sectionNameColor());
    painter->drawText(x, y, sectionName);

    painter->restore();
}

QSize ChatListDelegate::chatItemSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize{option.rect.width(), 65};
}

QSize ChatListDelegate::sectionSeparatorSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize{option.rect.width(), 30};
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
