#include "ui/components/roundwidget.h"

#include <QPainterPath>
#include <QPainter>

RoundWidget::RoundWidget(QWidget *parent)
    : QWidget(parent)
{

}

void RoundWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setOpacity(opacity_);

    QPainterPath roundedRect;
    roundedRect.addRoundedRect(rect(), cornerRadius_, cornerRadius_);

    painter.fillPath(roundedRect, backgroundColor_);
}

float RoundWidget::opacity() const
{
    return opacity_;
}

void RoundWidget::setOpacity(float newOpacity)
{
    if (qFuzzyCompare(opacity_, newOpacity))
        return;
    opacity_ = newOpacity;
    emit opacityChanged();
}

int RoundWidget::cornerRadius() const
{
    return cornerRadius_;
}

void RoundWidget::setCornerRadius(int newCornerRadius)
{
    if (cornerRadius_ == newCornerRadius)
        return;
    cornerRadius_ = newCornerRadius;
    emit cornerRadiusChanged();
}

QColor RoundWidget::backgroundColor() const
{
    return backgroundColor_;
}

void RoundWidget::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (backgroundColor_ == newBackgroundColor)
        return;
    backgroundColor_ = newBackgroundColor;
    emit backgroundColorChanged();
}
