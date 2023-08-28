#include "ui/components/fieldlineedit.h"

#include "ui/components/colorrepository.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QFontMetrics>
#include <QToolTip>
#include <QDebug>

inline QColor normalColor()
{
    return Colors.value(colornames::decorationColor);
}

inline QColor invalidColor()
{
    return Colors.value(colornames::beautyRedColor);
}

FieldLineEdit::FieldLineEdit(const QString &placeholder, QWidget *parent)
    : QLineEdit{parent}
{
    init(placeholder);
}

void FieldLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QPainter painter{this};

    const auto x = 0;
    const auto y = height() - LineWidth / 2;

    painter.setPen(QPen{lineColor_, LineWidth});
    painter.drawLine(QLine{x, y, width(), y});
}

void FieldLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    showValidInputState();
}

void FieldLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    if (!hasAcceptableInput()) {
        showInvalidInputState();
    }
}

void FieldLineEdit::init(const QString &placeholder)
{
    lineColor_ = Colors.value(colornames::decorationColor);
    textColor_ = Colors.value(colornames::mainLabelColor);
    placeholderColor_ = Colors.value(colornames::secondaryLabelColor);

    setFrame(false);

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::transparent);
    p.setColor(QPalette::PlaceholderText, Colors.value(colornames::secondaryLabelColor));
    p.setColor(QPalette::Highlight, Colors.value(colornames::decorationColor));
    p.setColor(QPalette::Text, Colors.value(colornames::mainLabelColor));
    setPalette(p);

    setPlaceholderText(placeholder);
}

void FieldLineEdit::showValidInputState()
{
    changeColor(normalColor());
    validInputState_ = true;
}

void FieldLineEdit::showInvalidInputState()
{
    changeColor(invalidColor());
    validInputState_ = false;
}

bool FieldLineEdit::isValid() const
{
    return hasAcceptableInput() && validInputState_;
}

void FieldLineEdit::startColorAnimation(const QColor &start, const QColor &end)
{
    QPropertyAnimation *colorAnim = new QPropertyAnimation{this, "lineColor"};
    colorAnim->setStartValue(start);
    colorAnim->setEndValue(end);
    colorAnim->setDuration(200);

    colorAnim->start(QAbstractAnimation::DeleteWhenStopped);
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
    update();
    emit lineColorChanged();
}

void FieldLineEdit::changeColor(const QColor &color)
{
    startColorAnimation(lineColor_, color);
}
