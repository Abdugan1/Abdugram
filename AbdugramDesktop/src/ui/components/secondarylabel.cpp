#include "ui/components/secondarylabel.h"

#include "ui/components/colorrepository.h"

SecondaryLabel::SecondaryLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel{parent, f}
{
    init();
}

SecondaryLabel::SecondaryLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel{text, parent, f}
{
    init();
}

void SecondaryLabel::setPointSize(int pointSize)
{
    QFont f = font();
    f.setPointSize(pointSize);
    setFont(f);
}

void SecondaryLabel::setBold(bool bold)
{
    QFont f = font();
    f.setBold(bold);
    setFont(f);
}

void SecondaryLabel::init()
{
    QPalette p = palette();
    p.setColor(QPalette::WindowText, Colors.value(colornames::secondaryLabelColor));
    setPalette(p);
}
