#include "mainlabel.h"

MainLabel::MainLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel{parent, f}
{

}

MainLabel::MainLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel{text, parent, f}
{

}
