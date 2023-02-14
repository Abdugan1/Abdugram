#include "imagebutton.h"
#include "rippleanimation.h"

#include <QDebug>

ImageButton::ImageButton(const QPixmap &pixmap)
{
    init(pixmap);
}

void ImageButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    rippleAnimation_->drawRipple();
}

void ImageButton::init(const QPixmap &pixmap)
{
    setCursor(Qt::PointingHandCursor);
    setIcon(pixmap);

    rippleAnimation_ = new RippleAnimation{this};
    rippleAnimation_->setAppearTime(400);
    rippleAnimation_->setDisappearTime(400);
    rippleAnimation_->setEndOpacity(0.15);

    connect(rippleAnimation_, &RippleAnimation::opacityChanged, this, [this]() {
        update();
    });

    installEventFilter(rippleAnimation_);
}
