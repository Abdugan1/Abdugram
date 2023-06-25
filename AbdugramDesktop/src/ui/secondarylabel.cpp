#include "ui/secondarylabel.h"

SecondaryLabel::SecondaryLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel{parent, f}
{

}

SecondaryLabel::SecondaryLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel{text, parent, f}
{

}
