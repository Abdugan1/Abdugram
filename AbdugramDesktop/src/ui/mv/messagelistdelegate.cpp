#include "ui/mv/messagelistdelegate.h"
#include "ui/mv/messagelistmodel.h"

#include "net/networkhandler.h"

#include <QTextEdit>
#include <QLabel>
#include <QTextBrowser>
#include <QTextDocument>
#include <QTextBlock>
#include <QStyle>
#include <QPainter>

const int MaxWidth_ = 400;
const int Radius_   = 20;

const int HSpacing_ = 15;
const int VSpacing_ = 7;

const int TimeSpacing = 10;

const QMargins BackgroundPaddings_ = QMargins{20, 20, 20, 20};

QTextOption textOption()
{
    QTextOption to;
    to.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    to.setAlignment(Qt::AlignLeft);
    return to;
}

QStringList splitMessageTextByLines(const QModelIndex &index)
{
    const QString text = index.data(MessageListModel::Text).toString();

    QTextDocument doc;
    doc.setPlainText(text);
    doc.setDefaultTextOption(textOption());
    doc.setTextWidth(MaxWidth_);

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

    setPainterOrigin(painter, option, index);

    drawBackground(painter, option, index);
    drawMessageText(painter, option, index);
    drawTime(painter, option, index);

    painter->restore();
}

QSize MessageListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize{option.rect.width(), getBackgroundRect(option, index).height() + VSpacing_ * 2};
}

void MessageListDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundColor_);
    painter->drawRoundedRect(getBackgroundRect(option, index), Radius_, Radius_);

    painter->restore();
}

void MessageListDelegate::drawMessageText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const auto text = splitMessageTextByLines(index).join('\n');

    QRect rect = getTextRect(text, option);
    rect.moveTopLeft(QPoint{BackgroundPaddings_.left(), BackgroundPaddings_.top()}
                     + option.rect.topLeft());


    // Use this instead?
//    option.widget->style()->drawItemText(painter, rect, Qt::AlignLeft, option.widget->palette(), true, text);

    painter->setPen(textColor_);
    painter->drawText(rect, text);

    painter->restore();
}

void MessageListDelegate::drawTime(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    const auto backgroundRect = getBackgroundRect(option, index);

    const auto lines = splitMessageTextByLines(index);
    const QString text = lines.join('\n');
    const QRect textRect = getTextRect(text, option);

    const QString time = index.data(MessageListModel::DateTime).toDateTime(). toString("hh:mm");
    QRect timeRect = getTextRect(time, option);

    auto lastLineBoundingRect = getTextRect(lines.last(), option);
    lastLineBoundingRect.moveTop(option.rect.top() + BackgroundPaddings_.top() + textRect.bottom() - lastLineBoundingRect.height());

    timeRect.moveRight(backgroundRect.right() - BackgroundPaddings_.right());

    timeRect.moveBottom(option.rect.bottom() - BackgroundPaddings_.bottom());

    painter->setPen(timeColor_);
    painter->drawText(timeRect, time);

    painter->restore();
}

QRect MessageListDelegate::getBackgroundRect(const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QRect rect;

    const auto lines = splitMessageTextByLines(index);
    const QRect textRect = getTextRect(lines.join('\n'), option);

    const QString time = index.data(MessageListModel::DateTime).toDateTime().toString("hh:mm");
    const QRect timeRect = getTextRect(time, option);

    const QRect lastLineRect = getTextRect(lines.last(), option);

    rect = textRect;

    if (lastLineRect.width() + TimeSpacing + timeRect.width() < MaxWidth_) {
        rect.setWidth(rect.width() + TimeSpacing + timeRect.width());
    } else {
        rect.setBottom(rect.bottom() + timeRect.height());
    }

    rect += BackgroundPaddings_;

    rect.moveTopLeft(option.rect.topLeft());

    return rect;
}

QRect MessageListDelegate::getTextRect(const QString &text, const QStyleOptionViewItem &option)
{
    return option.fontMetrics.boundingRect(0, 0, MaxWidth_, INT_MAX, Qt::AlignLeft | Qt::TextWrapAnywhere, text);
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

    const int myId = networkHandler()->userId();

    const int dx = senderId != myId ? HSpacing_ : fullWidth - HSpacing_ - bgWidth;
    const int dy = VSpacing_;

    painter->translate(dx, dy);
}
