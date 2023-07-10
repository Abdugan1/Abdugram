#include "ui/sidemenubutton.h"
#include "ui/rippleanimation.h"

SideMenuButton::SideMenuButton(const QString &text, QWidget *parent)
    : QPushButton{text, parent}
{
    init();
}

void SideMenuButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    if (rippleAnimation_->hasRipple())
        rippleAnimation_->drawRipple();
}

void SideMenuButton::init()
{
    rippleAnimation_ = new RippleAnimation{this};
    setFocusPolicy(Qt::NoFocus);
}
