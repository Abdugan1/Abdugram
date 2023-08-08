#include "ui/effects/rippleanimation.h"

#include <QWidget>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

#include <cmath>

const QEasingCurve EasingCurve = QEasingCurve::OutQuad;
const int MaxRippleOpacity = 35;
const int AnimationDuration = 450;


RippleAnimation::RippleAnimation(QWidget *parent)
    : QObject{parent}
    , parent_{parent}
{
    QStateMachine *stateMachine = new QStateMachine{this};

    QState *noRippleState = new QState{stateMachine};
    // Without setting rippleRadius to maximum, we dont get normal ripple
    // Ripple radius is set to 0 in startRipple
    noRippleState->assignProperty(this, "rippleRadius", parentDiagonal());
    noRippleState->assignProperty(this, "rippleOpacity", 0);

    QState *hasRippleState = new QState{stateMachine};
    hasRippleState->assignProperty(this, "rippleRadius", parentDiagonal());
    hasRippleState->assignProperty(this, "rippleOpacity", MaxRippleOpacity);

    auto radiusAnimation   = new QPropertyAnimation{this, "rippleRadius"};
    radiusAnimation->setDuration(AnimationDuration);
    radiusAnimation->setEasingCurve(EasingCurve);

    auto opacityAnimation1 = new QPropertyAnimation{this, "rippleOpacity"};
    opacityAnimation1->setDuration(AnimationDuration);
    opacityAnimation1->setEasingCurve(EasingCurve);

    auto group = new QParallelAnimationGroup{this};
    group->addAnimation(radiusAnimation);
    group->addAnimation(opacityAnimation1);

    auto transition1 = noRippleState->addTransition(this, &RippleAnimation::startRippleSignal, hasRippleState);
    transition1->addAnimation(group);

    auto opacityAnimation2 = new QPropertyAnimation{this, "rippleOpacity"};
    opacityAnimation2->setDuration(AnimationDuration);
    opacityAnimation2->setEasingCurve(EasingCurve);

    auto transition2 = hasRippleState->addTransition(this, &RippleAnimation::endRippleSignal, noRippleState);
    transition2->addAnimation(group);

    stateMachine->setInitialState(noRippleState);
    stateMachine->start();

    parent_->installEventFilter(this);
    connect(this, &RippleAnimation::rippleOpacityChanged, parent_, QOverload<>::of(&QWidget::update));
}

bool RippleAnimation::eventFilter(QObject *watched, QEvent *event)
{
    if (parent_->isEnabled()) {
        if (event->type() == QEvent::MouseButtonPress) {
            auto mouseEvent = static_cast<QMouseEvent *>(event);
            startRipple(mouseEvent->pos());
        } else if (event->type() == QEvent::MouseButtonRelease) {
            endRipple();
        }
    }
    return QObject::eventFilter(watched, event);
}

void RippleAnimation::drawRipple(QPainter *painter) const
{
    if (rippleOpacity_ ==  0) {
        return;
    }
    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor{255, 255, 255, rippleOpacity_});
    painter->drawEllipse(startPos_, rippleRadius_, rippleRadius_);

    painter->restore();
}

int RippleAnimation::rippleRadius() const
{
    return rippleRadius_;
}

void RippleAnimation::setRippleRadius(int newRippleRadius)
{
    if (rippleRadius_ == newRippleRadius)
        return;
    rippleRadius_ = newRippleRadius;
    emit rippleRadiusChanged();
}

int RippleAnimation::rippleOpacity() const
{
    return rippleOpacity_;
}

void RippleAnimation::setRippleOpacity(int newRippleOpacity)
{
    if (rippleOpacity_ == newRippleOpacity)
        return;
    rippleOpacity_ = newRippleOpacity;
    emit rippleOpacityChanged();
}

void RippleAnimation::startRipple(const QPoint &startPos)
{
    startPos_ = startPos;
    setRippleRadius(0);

    emit startRippleSignal();
}

void RippleAnimation::endRipple()
{
    emit endRippleSignal();
}

int RippleAnimation::parentDiagonal() const
{
    const auto w = parent_->width();
    const auto h = parent_->height();
    return std::sqrt(w * w + h * h);
}


