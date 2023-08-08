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

const int MaxWidth = 400;

const int MessageBackgroundRadius = 21;

const int HSpacingMessage = 7;
const int VSpacingMessage = 1;

const int VSpacingDateSeparator = 7;

const int TimeSpacing = 7;

const QMargins MessagePaddings       = QMargins{17, 10, 17, 10};
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

QTextOption textOption()
{
    QTextOption to;
    to.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    to.setAlignment(Qt::AlignLeft);
    return to;
}

QStringList splitMessageTextByLines(const QModelIndex &index)
{
    const QString text = index.data(MessageItem::Text).toString();

    QTextDocument doc;
    doc.setPlainText(text);
    doc.setDefaultTextOption(textOption());
    doc.setTextWidth(MaxWidth);

    doc.documentLayout();

    QStringList lines;
    QTextBlock textBlock = doc.begin();
    while(textBlock.isValid()) {
        QString blockText = textBlock.text();

        if(!textBlock.layout())
            continue;

        for(int i = 0; i != textBlock.layout()->lineCount(); ++i) {
            QTextLine line = textBlock.layout()->lineAt(i);
            lines.append(blockText.mid(line.textStart(), line.textLength()));
        }

        textBlock = textBlock.next();
    }

    return lines;
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

    const int type = index.data(static_cast<int>(MessageModelItem::Roles::Type)).toInt();
    switch (static_cast<MessageModelItem::Type>(type)) {
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

    const int type = index.data(static_cast<int>(MessageModelItem::Roles::Type)).toInt();
    switch (static_cast<MessageModelItem::Type>(type)) {
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

    const auto text = splitMessageTextByLines(index).join('\n');

    QRect rect = getTextRect(text, option.font);
    rect.moveTopLeft(QPoint{MessagePaddings.left(), MessagePaddings.top()});

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

    const auto lines = splitMessageTextByLines(index);
    const QString text = lines.join('\n');
    const QRect textRect = getTextRect(text, option.font);

    const QString time = index.data((MessageItem::Roles::DateTime)).toDateTime().toString("hh:mm");
    QRect timeRect = getTextRect(time, option.font);

    auto lastLineBoundingRect = getTextRect(lines.last(), option.font);
    lastLineBoundingRect.moveTop(MessagePaddings.top()
                                 + textRect.height() - lastLineBoundingRect.height());

    timeRect.moveRight(backgroundRect.right() - MessagePaddings.right());

    timeRect.moveBottom(lastLineBoundingRect.bottom() + TimeSpacing);

    QFont f = option.font;
    f.setPointSizeF(10.5);
    painter->setFont(f);
    painter->setPen(messageTimeColor());
    painter->drawText(timeRect, time);

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

    const auto lines = splitMessageTextByLines(index);
    const QRect textRect = getTextRect(lines.join('\n'), option.font);

    const QString time = index.data(MessageItem::DateTime).toDateTime().toString("hh:mm");
    const QRect timeRect = getTextRect(time, option.font);

    const QRect lastLineRect = getTextRect(lines.last(), option.font);

    rect = textRect;

    if (lastLineRect.width() + TimeSpacing + timeRect.width() < MaxWidth) {
        rect.setWidth(rect.width() + TimeSpacing + timeRect.width());
    } else {
        rect.setBottom(rect.bottom() + timeRect.height());
    }

    rect = QRect{0, 0,
                 rect.width() + MessagePaddings.left() + MessagePaddings.right(),
                 rect.height() + MessagePaddings.top() + MessagePaddings.bottom()};

    return rect;
}

QRect MessageListDelegate::getDateSeparatorBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const auto stringDate = dateToString(index);
    const auto textRect = getTextRect(stringDate, option.font);
    return QRect{0, 0,
                 textRect.width() + DateSeparatorPaddings.left() + DateSeparatorPaddings.right(),
                 textRect.height() + DateSeparatorPaddings.top() + DateSeparatorPaddings.bottom()};
}

QRect MessageListDelegate::getTextRect(const QString &text, const QFont &font) const
{
    return QFontMetrics{font}.boundingRect(0, 0, MaxWidth, INT_MAX,
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
