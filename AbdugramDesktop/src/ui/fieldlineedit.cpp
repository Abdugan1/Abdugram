#include "ui/fieldlineedit.h"

#include <QPainter>
#include <QFontMetrics>
#include <QToolTip>
#include <QDebug>

FieldLineEdit::FieldLineEdit(const QString &placeholder, QWidget *parent)
    : LineEdit{parent}
{
    setPlaceholderText(placeholder);
}

void FieldLineEdit::paintEvent(QPaintEvent *event)
{
    LineEdit::paintEvent(event);

    int textHeight  = QFontMetrics(font()).height();

    QRect lineRect{QPoint{0, textHeight + textMargins().top()},
                   rect().bottomRight()};

    QPainter painter{this};
    painter.setPen(Qt::NoPen);
    painter.setBrush(lineColor_);
    painter.setOpacity(0.6);
    painter.drawRect(lineRect);
}

void FieldLineEdit::focusInEvent(QFocusEvent *event)
{
    LineEdit::focusInEvent(event);
    showValidInputState();
}

void FieldLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    if (!hasAcceptableInput()) {
        showInvalidInputState();
    }
}

void FieldLineEdit::showValidInputState()
{
    static QColor defaultColor = lineColor();
    setLineColor(defaultColor);
}

void FieldLineEdit::showInvalidInputState()
{
    setLineColor(Qt::red);
}

QColor FieldLineEdit::lineColor() const
{
    return lineColor_;
}

void FieldLineEdit::setLineColor(const QColor &newLineColor)
{
    if (lineColor_ == newLineColor)
        return;
    lineColor_ = newLineColor;
    emit lineColorChanged();
}
