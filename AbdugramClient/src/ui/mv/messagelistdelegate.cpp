#include "messagelistdelegate.h"
#include "messagelistmodel.h"

#include <QPainter>

const int MessageListDelegate::MaxWidth_ = 400;
const int MessageListDelegate::Radius_   = 20;
const int MessageListDelegate::TempMyId_ = 0;

const int MessageListDelegate::HMargin_ = 15;
const int MessageListDelegate::VMargin_ = 7;

const QMargins MessageListDelegate::BackgroundPaddings_ = QMargins{20, 20, 20, 20};

MessageListDelegate::MessageListDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void MessageListDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);

    setPainterOrigin(painter, option, index);

    drawBackground(painter, option, index);
    drawText(painter, option, index);
    drawTime(painter, option, index);

    painter->restore();
}

QSize MessageListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize{option.rect.width(), getBackgroundRect(option, index).height() + 2 * VMargin_};
}

void MessageListDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundColor_);
    painter->drawRoundedRect(getBackgroundRect(option, index), Radius_, Radius_);

    painter->restore();
}

void MessageListDelegate::drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const QString text = index.data(MessageListModel::Text).toString();
    QRect rect = getTextRect(text, option);
    rect.moveTopLeft(QPoint{BackgroundPaddings_.left(), BackgroundPaddings_.top()} + option.rect.topLeft());

    painter->setPen(textColor_);
    painter->drawText(rect, text);

    painter->restore();
}

void MessageListDelegate::drawTime(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const QString time = index.data(MessageListModel::DateTime).toDateTime(). toString("hh:mm");
    QRect timeRect = getTextRect(time, option);

    const QString text = index.data(MessageListModel::Text).toString();
    QRect textRect = getTextRect(text, option);

    timeRect.moveBottomRight(QPoint{textRect.right() + BackgroundPaddings_.right(),
                                    option.rect.bottom() - BackgroundPaddings_.bottom()});

    painter->setPen(timeColor_);
    painter->drawText(timeRect, time);

    painter->restore();
}

QRect MessageListDelegate::getBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QRect rect;

    const QString text = index.data(MessageListModel::Text).toString();
    QRect textRect = getTextRect(text, option);

    const QString time = index.data(MessageListModel::DateTime).toDateTime().toString("hh:mm");
    QRect timeRect = getTextRect(time, option);

    rect = textRect;
    rect.setBottom(rect.bottom() + timeRect.height());
    rect += BackgroundPaddings_;

    rect.moveTopLeft(option.rect.topLeft());

    return rect;
}

QRect MessageListDelegate::getTextRect(const QString &text, const QStyleOptionViewItem &option)
{
    return option.fontMetrics.boundingRect(0, 0, MaxWidth_, INT_MAX, Qt::AlignLeft | Qt::TextWordWrap, text);
}

QColor MessageListDelegate::backgroundColor() const
{
    return backgroundColor_;
}

void MessageListDelegate::setBackgroundColor(const QColor &newBackgroundColor)
{
    backgroundColor_ = newBackgroundColor;
}

QColor MessageListDelegate::textColor() const
{
    return textColor_;
}

void MessageListDelegate::setTextColor(const QColor &newTextColor)
{
    textColor_ = newTextColor;
}

QColor MessageListDelegate::timeColor() const
{
    return timeColor_;
}

void MessageListDelegate::setTimeColor(const QColor &newTimeColor)
{
    timeColor_ = newTimeColor;
}

void MessageListDelegate::setPainterOrigin(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int senderId = index.data(MessageListModel::SenderId).toInt();

    const int fullWidth = option.rect.width();
    const int bgWidth   = getBackgroundRect(option, index).width();

    const int dx = senderId != TempMyId_ ? HMargin_ : fullWidth - HMargin_ - bgWidth;
    const int dy = VMargin_;

    painter->translate(dx, dy);
}
