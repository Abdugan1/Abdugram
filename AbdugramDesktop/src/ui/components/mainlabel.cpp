#include "ui/components/mainlabel.h"

#include "ui/components/colorrepository.h"

MainLabel::MainLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel{parent, f}
{
    init();
}

MainLabel::MainLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel{text, parent, f}
{
    init();
}

void MainLabel::init()
{
    QPalette p = palette();
    p.setColor(QPalette::WindowText, Colors.value(colornames::mainLabelColor));
    setPalette(p);
}
