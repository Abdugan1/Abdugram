#include "ui/mv/messagelistdelegate.h"
#include "ui/mv/messageitem.h"
#include "ui/mv/dateseparatoritem.h"

#include "ui/components/colorrepository.h"

#include "net/networkhandler.h"

#include <QTextEdit>
#include <QLabel>
#include <QTextBrowser>
#include <QTextDocument>
#include <QTextBlock>
#include <QStyle>
#include <QPainter>

const int MessageBackgroundRadius = 21;

const int HSpacingMessage = 7;
const int VSpacingMessage = 1;

const int VSpacingDateSeparator = 7;

const QMargins DateSeparatorPaddings = QMargins{17, 5, 17, 5};

inline QColor messageBackgroundColorWhenSenderIsMe()
{
    return Colors.value(colornames::decorationColor);
}

inline QColor messageBackgroundColorWhenSenderIsOther()
{
    return Colors.value(colornames::backgroundLighterHelper4);
}

inline QColor messageTextColor()
{
    return Colors.value(colornames::mainLabelColor);
}

inline QColor messageTimeColor()
{
    return Colors.value(colornames::mainLabelColor);
}

inline QColor dateSeparatorBackgroundColor()
{
    return Colors.value(colornames::backgroundLighterHelper3);
}

inline QColor dateColor()
{
    return Colors.value(colornames::mainLabelColor);
}

inline bool senderIsMe(const QModelIndex &index)
{
    return networkHandler()->userId() == index.data(MessageItem::Roles::SenderId).toInt();
}

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

    const int type = index.data(MessageModelItem::Roles::Type).toInt();
    switch (type) {
    case MessageModelItem::Type::MessageItem:
        drawMessageItem(painter, option, index);
        break;
    case MessageModelItem::Type::DateSeparatorItem:
        drawDateSeparatorItem(painter, option, index);
        break;
    }

    painter->restore();
}

QSize MessageListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    const int type = index.data(MessageModelItem::Roles::Type).toInt();
    switch (type) {
    case MessageModelItem::Type::MessageItem:
        return messageSizeHint(option, index);
        break;
    case MessageModelItem::Type::DateSeparatorItem:
        return dateSeparatorSizeHint(option, index);
        break;
    }

    return QSize{};
}

void MessageListDelegate::setPainterOriginOnMessage(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int fullWidth = option.rect.width();
    const int bgWidth   = getMessageBackgroundRect(option, index).width();

    const int dx = !senderIsMe(index) ? HSpacingMessage : fullWidth - HSpacingMessage - bgWidth;
    const int dy = option.rect.top() + VSpacingMessage;

    painter->translate(dx, dy);
}

void MessageListDelegate::drawMessageItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    setPainterOriginOnMessage(painter, option, index);

    drawMessageBackground(painter, option, index);
    drawMessageText(painter, option, index);
    drawMessageTime(painter, option, index);
    drawMessageIsRead(painter, option, index);

    painter->restore();
}

void MessageListDelegate::drawMessageBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(senderIsMe(index) ? messageBackgroundColorWhenSenderIsMe()
                                        : messageBackgroundColorWhenSenderIsOther());

    painter->drawRoundedRect(getMessageBackgroundRect(option, index),
                             MessageBackgroundRadius, MessageBackgroundRadius);

    painter->restore();
}

void MessageListDelegate::drawMessageText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const auto text = index.data(MessageItem::SplittedText).toStringList().join('\n');

    QRect rect = getTextRect(text, option.font);
    rect.moveTopLeft(QPoint{MessageItem::BackgroundLeftPadding, MessageItem::BackgroundTopPadding});

    // Use this instead?
//    option.widget->style()->drawItemText(painter, rect, Qt::AlignLeft, option.widget->palette(), true, text);

    painter->setPen(messageTextColor());
    painter->drawText(rect, text);

    painter->restore();
}

void MessageListDelegate::drawMessageTime(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const auto backgroundRect = getMessageBackgroundRect(option, index);

    const auto lines = index.data(MessageItem::SplittedText).toStringList();
    const QString text = lines.join('\n');
    const QRect textRect = getTextRect(text, option.font);

    const QString time = index.data((MessageItem::Roles::DateTime)).toDateTime().toString("hh:mm");
    QRect timeRect = getTextRect(time, option.font);

    auto lastLineBoundingRect = getTextRect(lines.last(), option.font);
    lastLineBoundingRect.moveTop(MessageItem::BackgroundTopPadding + textRect.height() - lastLineBoundingRect.height());

    timeRect.moveRight(backgroundRect.right() - MessageItem::BackgroundRightPadding - (senderIsMe(index) ? MessageItem::IsReadWidth : 0));

    if (lastLineFullWidth(lastLineBoundingRect, timeRect, senderIsMe(index)) <= MessageItem::MaxContentWidth)
        timeRect.moveBottom(lastLineBoundingRect.bottom() + MessageItem::TimeVSpacing);
    else
        timeRect.moveBottom(lastLineBoundingRect.bottom() + timeRect.height());

    QFont f = option.font;
    f.setPointSizeF(f.pointSizeF() - 0.5);
    painter->setFont(f);
    painter->setPen(messageTimeColor());
    painter->drawText(timeRect, time);

    painter->restore();
}

void MessageListDelegate::drawMessageIsRead(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!senderIsMe(index))
        return;

    painter->save();

    const auto backgroundRect = getMessageBackgroundRect(option, index);

    const QColor checkColor = (index.data(MessageItem::IsRead).toBool() ? Qt::cyan
                                                                        : Qt::red);
    QPen pen{checkColor, 10, Qt::SolidLine, Qt::RoundCap};
    painter->setPen(pen);

    painter->drawPoint(backgroundRect.right() - MessageItem::BackgroundRightPadding,
                       backgroundRect.bottom() - MessageItem::BackgroundBottomPadding);

    painter->restore();
}

void MessageListDelegate::setPainterOriginOnDateSeparator(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const auto bgRect = getDateSeparatorBackgroundRect(option, index);
    painter->translate(option.rect.width() / 2 - bgRect.width() / 2,
                       option.rect.top() + VSpacingDateSeparator);
}

void MessageListDelegate::drawDateSeparatorItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    setPainterOriginOnDateSeparator(painter, option, index);

    drawDateSeparatorBackground(painter, option, index);
    drawDateSeparatorDate(painter, option, index);

    painter->restore();
}

void MessageListDelegate::drawDateSeparatorBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(dateSeparatorBackgroundColor());

    const auto rect = getDateSeparatorBackgroundRect(option, index);
    painter->drawRoundedRect(rect, rect.height() / 2, rect.height() / 2);

    painter->restore();
}

void MessageListDelegate::drawDateSeparatorDate(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setPen(dateColor());

    const auto text = dateToString(index);
    auto rect = getTextRect(text, option.font);
    rect.moveTopLeft(QPoint{DateSeparatorPaddings.left(), DateSeparatorPaddings.top()});

    painter->drawText(rect, dateToString(index));

    painter->restore();
}

QSize MessageListDelegate::messageSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QRect bgRect = getMessageBackgroundRect(option, index);
    return QSize{bgRect.width() + HSpacingMessage * 2, bgRect.height() + VSpacingMessage * 2};
}

QSize MessageListDelegate::dateSeparatorSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const auto bgRect = getDateSeparatorBackgroundRect(option, index);
    return QSize{bgRect.width(), bgRect.height() + VSpacingDateSeparator * 2};
}

QRect MessageListDelegate::getMessageBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect;

    const auto  lines    = index.data(MessageItem::SplittedText).toStringList();
    const QRect textRect = getTextRect(lines.join('\n'), option.font);

    const QString time     = index.data(MessageItem::DateTime).toDateTime().toString("hh:mm");
    const QRect   timeRect = getTextRect(time, option.font);

    const QRect lastLineRect = getTextRect(lines.last(), option.font);

    rect = textRect;

    if (lastLineFullWidth(lastLineRect, timeRect, senderIsMe(index)) <= MessageItem::MaxContentWidth) {
        rect.setWidth(rect.width() + MessageItem::TimeHSpacing + timeRect.width());
    } else {
        rect.setBottom(rect.bottom() + timeRect.height());
    }
    if (senderIsMe(index))
        rect.setWidth(rect.width() + MessageItem::IsReadWidth);

    rect = QRect{0, 0,
                 rect.width()  + MessageItem::BackgroundLeftPadding + MessageItem::BackgroundRightPadding,
                 rect.height() + MessageItem::BackgroundTopPadding  + MessageItem::BackgroundBottomPadding};

    return rect;
}

QRect MessageListDelegate::getDateSeparatorBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const auto stringDate = dateToString(index);
    const auto textRect = getTextRect(stringDate, option.font);
    return QRect{0, 0,
                 textRect.width()  + DateSeparatorPaddings.left() + DateSeparatorPaddings.right(),
                 textRect.height() + DateSeparatorPaddings.top() + DateSeparatorPaddings.bottom()};
}

QRect MessageListDelegate::getTextRect(const QString &text, const QFont &font) const
{
    return QFontMetrics{font}.boundingRect(0, 0, MessageItem::MaxContentWidth, INT_MAX,
                                           Qt::AlignLeft | Qt::TextWrapAnywhere, text);
}

QString MessageListDelegate::dateToString(const QModelIndex &index) const
{
    const auto date = index.data(DateSeparatorItem::Date).toDate();
    if (date.year() == QDate::currentDate().year()) {
        return date.toString("MMMM d");
    }
    return date.toString("MMMM d, yyyy");
}

int MessageListDelegate::lastLineFullWidth(const QRect &lastLineRect, const QRect &timeRect, bool senderIsMe) const
{
    return lastLineRect.width() + MessageItem::TimeHSpacing + timeRect.width() + (senderIsMe ? MessageItem::IsReadWidth : 0);
}
