#include "messagelistview.h"
#include "messagelistmodel.h"
#include "messagelistdelegate.h"

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
