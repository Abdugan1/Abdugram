#include "lineedit.h"

#include <QPainter>
#include <QFontMetrics>

LineEdit::LineEdit(const QString &placeholder, QWidget *parent)
    : QLineEdit{parent}
{
    setPlaceholderText(placeholder);
}

void LineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    int textHeight  = QFontMetrics(font()).height();

    QRect lineRect{QPoint{0, textHeight + textMargins().top()},
                   rect().bottomRight()};

    QPainter painter{this};
    painter.setPen(Qt::NoPen);
    painter.setBrush(lineColor_);
    painter.setOpacity(0.6);
    painter.drawRect(lineRect);
}

QColor LineEdit::lineColor() const
{
    return lineColor_;
}

void LineEdit::setLineColor(const QColor &newLineColor)
{
    if (lineColor_ == newLineColor)
        return;
    lineColor_ = newLineColor;
    emit lineColorChanged();
}
