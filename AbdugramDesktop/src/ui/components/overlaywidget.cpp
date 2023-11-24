#include "ui/components/overlaywidget.h"

#include <QMouseEvent>

OverlayWidget::OverlayWidget(QWidget *parent)
    : QWidget(parent)
{

}

void OverlayWidget::mousePressEvent(QMouseEvent *event)
{
    if (!widget_->geometry().contains(event->pos())) {
        emit overlayClicked();
    }
    QWidget::mousePressEvent(event);
}

QWidget *OverlayWidget::widget() const
{
    return widget_;
}

void OverlayWidget::setWidget(QWidget *newWidget)
{
    widget_ = newWidget;
}
