#include "ui/button.h"
#include "ui/rippleanimation.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtMath>

Button::Button(QWidget *parent)
    : QPushButton(parent)
{
    init();
}

Button::Button(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    init();
}

Button::Button(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    init();
}

void Button::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    rippleAnimation_->drawRipple();
}

void Button::init()
{
    setCursor(Qt::PointingHandCursor);

    rippleAnimation_ = new RippleAnimation{this};
    rippleAnimation_->setAppearTime(400);
    rippleAnimation_->setDisappearTime(400);
    rippleAnimation_->setEndOpacity(0.15);

    connect(rippleAnimation_, &RippleAnimation::opacityChanged, this, [this]() {
        update();
    });

    installEventFilter(rippleAnimation_);
}


