#include "ui/mv/chatlistdelegate.h"
#include "ui/mv/chatlistmodel.h"

#include "ui/colorrepository.h"

#include <QPainter>
#include <QDebug>

using Roles = ChatListModel::Roles;

const QMargins ChatListDelegate::AvatarMargins_      = QMargins{5, 10, -1, 10};
const QSize    ChatListDelegate::AvatarSize_         = QSize{45, 45};
const QMargins ChatListDelegate::ChatNameMargins_    = QMargins{10, 8, -1, -1};
const QMargins ChatListDelegate::MessageDateMargins_ = QMargins{-1, 8, 5, -1};

const int ChatListDelegate::SeparatorThin_ = 1;

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

ChatListDelegate::ChatListDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void ChatListDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    painter->save();

    if (!isContentRectEqual(option))
        updateContentRect(option);

    if (option.state & QStyle::State_Selected)
        drawHighlight(painter, option, index);

    drawAvatar(painter, option, index);
    drawChatName(painter, option, index);
    drawLastMessage(painter, option, index);
    drawMessageDate(painter, option, index);
    drawSeparator(painter, option, index);

    painter->restore();
}

QSize ChatListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QSize{option.rect.width(), 65 + SeparatorThin_};
}

void ChatListDelegate::drawHighlight(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(highlightColor());
    painter->drawRect(contentRect_);

    painter->restore();
}

void ChatListDelegate::drawAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const int x = contentRect_.x() + AvatarMargins_.left();
    const int y = contentRect_.y() + AvatarMargins_.top();

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

    const int x = contentRect_.x() + AvatarMargins_.left() + AvatarSize_.width() + ChatNameMargins_.left();
    const int y = contentRect_.y() + ChatNameMargins_.top() + option.fontMetrics.height();

    const QString chatName = index.data(Roles::ChatName).toString();
    const int width = contentRect_.width() - x - MessageDateMargins_.right();
    const QString elidedName = option.fontMetrics.elidedText(chatName, Qt::ElideRight, width);
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

    const int x = contentRect_.x() + AvatarMargins_.left() + AvatarSize_.width() + ChatNameMargins_.left();
    const int y = contentRect_.y() + ChatNameMargins_.top() + option.fontMetrics.height() * 2;

    const QString lastMessage = index.data(Roles::LastMessage).toString();
    const int width = contentRect_.width() - x - MessageDateMargins_.right();
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

    int       x = contentRect_.right() - MessageDateMargins_.right();
    const int y = contentRect_.top() + MessageDateMargins_.top() + option.fontMetrics.height();

    const QString messageDate = index.data(Roles::MessageDate).toDateTime().toString("hh:mm");
    x -= option.fontMetrics.horizontalAdvance(messageDate);

    painter->drawText(x, y, messageDate);

    painter->restore();
}

void ChatListDelegate::drawSeparator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const int x = option.rect.x() + AvatarMargins_.left() + AvatarSize_.width() + ChatNameMargins_.left();
    const int y = contentRect_.bottom() + 1;

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::black);
    painter->drawRect(QRect{QPoint{x, y}, option.rect.bottomRight()});;

    painter->restore();
}

bool ChatListDelegate::isContentRectEqual(const QStyleOptionViewItem &option) const
{
    const auto &r = option.rect;
    const auto &c = contentRect_;
    return (c.x() == r.x()) && (c.y() == r.y())
            && (c.width() == r.width()) && (c.height() == r.height() - SeparatorThin_);
}

void ChatListDelegate::updateContentRect(const QStyleOptionViewItem &option) const
{
    const auto &r = option.rect;
    contentRect_ = QRect{r.x(), r.y(), r.width(), r.height() - SeparatorThin_};
}
