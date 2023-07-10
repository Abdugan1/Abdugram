#include "ui/imagebutton.h"
#include "ui/rippleanimation.h"

#include <QDebug>

ImageButton::ImageButton(const QPixmap &pixmap)
{
    init(pixmap);
}

void ImageButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    if (rippleAnimation_->hasRipple())
        rippleAnimation_->drawRipple();
}

void ImageButton::init(const QPixmap &pixmap)
{
    setCursor(Qt::PointingHandCursor);
    setIcon(pixmap);

    rippleAnimation_ = new RippleAnimation{this};
    setFocusPolicy(Qt::NoFocus);
}
