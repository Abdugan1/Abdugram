#include "messagelistview.h"
#include "messagelistmodel.h"
#include "messagelistdelegate.h"

#include <QPainter>

MessageListView::MessageListView(QWidget *parent)
    : QListView{parent}
    , model_{new MessageListModel{this}}
    , delegate_{new MessageListDelegate{this}}
{
    connect(this, &MessageListView::backgroundColorChanged, this, [this](){
        delegate_->setBackgroundColor(backgroundColor_);
    });
    connect(this, &MessageListView::textColorChanged, this, [this](){
        delegate_->setTextColor(textColor_);
    });
    connect(this, &MessageListView::timeColorChanged, this, [this](){
        delegate_->setTimeColor(timeColor_);
    });

    setModel(model_);
    setItemDelegate(delegate_);

    setVerticalScrollMode(QListView::ScrollPerPixel);

    setContentsMargins(0, 0, 0, 0);
}

QColor MessageListView::backgroundColor() const
{
    return backgroundColor_;
}

void MessageListView::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (backgroundColor_ == newBackgroundColor)
        return;
    backgroundColor_ = newBackgroundColor;
    emit backgroundColorChanged();
}

QColor MessageListView::textColor() const
{
    return textColor_;
}

void MessageListView::setTextColor(const QColor &newTextColor)
{
    if (textColor_ == newTextColor)
        return;
    textColor_ = newTextColor;
    emit textColorChanged();
}

QColor MessageListView::timeColor() const
{
    return timeColor_;
}

void MessageListView::setTimeColor(const QColor &newTimeColor)
{
    if (timeColor_ == newTimeColor)
        return;
    timeColor_ = newTimeColor;
    emit timeColorChanged();
}

void MessageListView::paintEvent(QPaintEvent *event)
{
    if (!model_->isEmpty()) {
        QListView::paintEvent(event);
    } else {
        drawSomething();
    }
}

void MessageListView::drawSomething()
{
    QPainter painter{viewport()};
    painter.setRenderHint(QPainter::Antialiasing);

    const QFontMetrics fm = painter.fontMetrics();
    const QString text    = tr("Select a chat to start messaging");
    const QRect textBRect = fm.boundingRect(text);
    const QPoint center = viewport()->rect().center();

    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor_);
    const int hMargin = 15;
    const int vMargin = 3;
    QRect background = QRect{center.x() - textBRect.width() / 2 - hMargin,
                             center.y() - fm.ascent() / 2 - vMargin,
                             textBRect.width() + 2 * hMargin,
                             textBRect.height() + 2 * vMargin};
    painter.drawRoundedRect(background, background.height() / 2, background.height() / 2);

    painter.setPen(textColor_);

    const QPoint textDrawPoint{center.x() - fm.horizontalAdvance(text) / 2,
                               center.y() + fm.ascent() / 2};

    painter.drawText(textDrawPoint, text);
}
