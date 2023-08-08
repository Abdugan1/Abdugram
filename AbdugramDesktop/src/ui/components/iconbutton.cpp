#include "ui/components/iconbutton.h"

#include "ui/effects/rippleanimation.h"

#include <QPainterPath>
#include <QPainter>
#include <QDebug>

IconButton::IconButton(const QPixmap &pixmap)
{
    init(pixmap);
}

void IconButton::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};

    QPixmap pixmap = icon().pixmap(iconSize());

    const auto r = rect();
    const auto bw = r.width();
    const auto bh = r.height();
    const auto pw = pixmap.width();
    const auto ph = pixmap.height();

    const auto x = bw / 2 - pw / 2;
    const auto y = bh / 2 - ph / 2;

    painter.drawPixmap(x, y, pixmap);

    QPainterPath path;
    path.addRoundedRect(r, bw / 2, bh / 2);
    painter.setClipPath(path);
    painter.setClipping(true);

    rippleAnimation_->drawRipple(&painter);
}

void IconButton::init(const QPixmap &pixmap)
{
    setCursor(Qt::PointingHandCursor);
    setIcon(pixmap);
    setIconSize(QSize{19, 19});
    setFixedSize(QSize{32, 32});

    setFocusPolicy(Qt::NoFocus);

    rippleAnimation_ = new RippleAnimation{this};
}
