#include "ui/welcomebutton.h"
#include "ui/rippleanimation.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtMath>

WelcomeButton::WelcomeButton(QWidget *parent)
    : QPushButton(parent)
{
    init();
}

WelcomeButton::WelcomeButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    init();
}

WelcomeButton::WelcomeButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    init();
}

void WelcomeButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    if (rippleAnimation_->hasRipple())
        rippleAnimation_->drawRipple();
}

void WelcomeButton::init()
{
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::NoFocus);

    rippleAnimation_ = new RippleAnimation{this};
}


