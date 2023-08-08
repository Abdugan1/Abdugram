#include "ui/components/widget.h"

#include "ui/components/colorrepository.h"

#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget{parent}
{
    setBackgroundColor(Colors.value(colornames::backgroundColor));
}

QColor Widget::backgroundColor() const
{
    return backgroundColor_;
}

void Widget::setBackgroundColor(const QColor &color)
{
    backgroundColor_ = color;
    QPalette p = palette();
    p.setColor(QPalette::Base, backgroundColor_);
    p.setColor(QPalette::Window, backgroundColor_);
    setPalette(p);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor_);
    painter.drawRect(rect());
}
