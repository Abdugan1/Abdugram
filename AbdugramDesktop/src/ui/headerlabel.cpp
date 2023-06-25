#include "ui/headerlabel.h"

HeaderLabel::HeaderLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel{parent, f}
{

}

HeaderLabel::HeaderLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel{text, parent, f}
{

}
