#include "ui/components/headerlabel.h"

#include "ui/components/colorrepository.h"

HeaderLabel::HeaderLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel{parent, f}
{
    init();
}

HeaderLabel::HeaderLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel{text, parent, f}
{
    init();
}

void HeaderLabel::init()
{
    QPalette p = palette();
    p.setColor(QPalette::WindowText, Colors.value(colornames::mainLabelColor));
    setPalette(p);

    QFont f = font();
    f.setBold(true);
    setFont(f);
}
