#include "searchlineedit.h"

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : LineEdit{parent}
{
    setAttribute(Qt::WA_MacShowFocusRect, false);
}
