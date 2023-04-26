#include "lineedit.h"

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit{parent}
{
    connect(this, &LineEdit::textEdited,              this, &LineEdit::setAppropriateColor);
    connect(this, &LineEdit::textColorChanged,        this, &LineEdit::setAppropriateColor);
    connect(this, &LineEdit::placeholderColorChanged, this, &LineEdit::setAppropriateColor);
}

QColor LineEdit::textColor() const
{
    return textColor_;
}

void LineEdit::setTextColor(const QColor &newTextColor)
{
    if (textColor_ == newTextColor)
        return;
    textColor_ = newTextColor;
    emit textColorChanged();
}

QColor LineEdit::placeholderColor() const
{
    return placeholderColor_;
}

void LineEdit::setPlaceholderColor(const QColor &newPlaceholderColor)
{
    if (placeholderColor_ == newPlaceholderColor)
        return;
    placeholderColor_ = newPlaceholderColor;
    emit placeholderColorChanged();
}

void LineEdit::setAppropriateColor()
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Text, text().isEmpty() ? placeholderColor_ : textColor_);
    setPalette(palette);
}
