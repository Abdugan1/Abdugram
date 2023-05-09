#include "textedit.h"

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit{parent}
{
    connect(this, &TextEdit::textChanged,             this, &TextEdit::setAppropriateColor);
    connect(this, &TextEdit::textColorChanged,        this, &TextEdit::setAppropriateColor);
    connect(this, &TextEdit::placeholderColorChanged, this, &TextEdit::setAppropriateColor);
}

QColor TextEdit::textColor() const
{
    return textColor_;
}

void TextEdit::setTextColor(const QColor &newTextColor)
{
    if (textColor_ == newTextColor)
        return;
    textColor_ = newTextColor;
    emit textColorChanged();
}

QColor TextEdit::placeholderColor() const
{
    return placeholderColor_;
}

void TextEdit::setPlaceholderColor(const QColor &newPlaceholderColor)
{
    if (placeholderColor_ == newPlaceholderColor)
        return;
    placeholderColor_ = newPlaceholderColor;
    emit placeholderColorChanged();
}

void TextEdit::setAppropriateColor()
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Text, document()->toPlainText().isEmpty() ? placeholderColor_ : textColor_);
    setPalette(palette);
}
