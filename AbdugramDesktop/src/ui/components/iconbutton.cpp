#include "ui/components/iconbutton.h"

#include "ui/effects/rippleanimation.h"

#include <QStyleOptionButton>
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
    painter.setPen(Qt::NoPen);

    drawBackground(&painter);
    drawIcon(&painter);


    const auto r = rect();
    const auto w = r.width();

    QPainterPath path;
    path.addRoundedRect(rect(), w / 2, w / 2);
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

void IconButton::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    const auto r = rect();
    const auto w = r.width();

    QColor bgColor = backgroundColor_;

    if (isEnabled()) {
        QStyleOptionButton opt;
        initStyleOption(&opt);

        if (opt.state & QStyle::State_MouseOver) {
            bgColor = bgColor.lighter(130);
        }

    }

    painter->setBrush(bgColor);
    painter->drawRoundedRect(r, w / 2, w / 2);

    painter->restore();
}

void IconButton::drawIcon(QPainter *painter)
{
    const QPixmap pixmap = icon().pixmap(iconSize());

    const auto r = rect();
    const auto bw = r.width();
    const auto pw = pixmap.width();

    const auto x = bw / 2 - pw / 2;
    const auto y = bw / 2 - pw / 2;

    painter->drawPixmap(x, y, pixmap);
}

QColor IconButton::backgroundColor() const
{
    return backgroundColor_;
}

void IconButton::setBackgroundColor(const QColor &newBackgroundColor)
{
    backgroundColor_ = newBackgroundColor;
}
