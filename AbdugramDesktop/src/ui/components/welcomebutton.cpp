#include "ui/components/welcomebutton.h"

#include "ui/components/colorrepository.h"

#include "ui/effects/rippleanimation.h"

#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionButton>
#include <QStateMachine>
#include <QState>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QMouseEvent>
#include <QtMath>
#include <QTimer>
#include <QDebug>

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
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (cornerRadius_ > 0) {
        QPainterPath path;
        path.addRoundedRect(rect(), cornerRadius_, cornerRadius_);

        painter.setClipPath(path);
        painter.setClipping(true);
    }

    drawBackground(&painter);
    drawText(&painter);

    rippleAnimation_->drawRipple(&painter);
}

void WelcomeButton::changeEvent(QEvent *event)
{
    QPushButton::changeEvent(event);
    if (event->type() == QEvent::EnabledChange) {
        if (isEnabled()) {
            emit enabled();
        } else {
            emit disabled();
        }
    }
}

void WelcomeButton::init()
{
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::NoFocus);

    cornerRadius_ = 5;

    disabledColor_ = Qt::gray;
    backgroundColor_ = Colors.value(colornames::decorationColor);
    textColor_ = Colors.value(colornames::mainLabelColor);

    setFixedHeight(35);

    QStateMachine *stateMachine = new QStateMachine{this};

    QState *enabledState = new QState{stateMachine};
    enabledState->assignProperty(this, "backgroundColor", backgroundColor_);

    QState *disabledState = new QState{stateMachine};
    disabledState->assignProperty(this, "backgroundColor", disabledColor_);

    const auto AnimDuration = 320;

    auto enabledToDisabledAnimation = new QPropertyAnimation{this, "backgroundColor"};
    enabledToDisabledAnimation->setDuration(AnimDuration);
    enabledToDisabledAnimation->setEasingCurve(QEasingCurve::OutCubic);

    auto disabledToEnabledAnimation = new QPropertyAnimation{this, "backgroundColor"};
    disabledToEnabledAnimation->setDuration(AnimDuration);
    disabledToEnabledAnimation->setEasingCurve(QEasingCurve::OutCubic);

    auto enabledToDisabled = enabledState->addTransition(this, &WelcomeButton::disabled, disabledState);
    enabledToDisabled->addAnimation(enabledToDisabledAnimation);

    auto disabledToEnabled = disabledState->addTransition(this, &WelcomeButton::enabled, enabledState);
    disabledToEnabled->addAnimation(disabledToEnabledAnimation);

    stateMachine->setInitialState(enabledState);

    // Ugly workaround.
    QTimer::singleShot(1, [=]() {
        stateMachine->setInitialState(isEnabled() ? enabledState : disabledState);
        stateMachine->start();
    });

    rippleAnimation_ = new RippleAnimation{this};
}

void WelcomeButton::drawBackground(QPainter *painter)
{
    painter->save();

    painter->setPen(Qt::NoPen);

    QStyleOptionButton option;
    option.initFrom(this);

    auto bgColor = backgroundColor_;
    if (option.state & QStyle::State_Enabled && option.state & QStyle::State_MouseOver)
        bgColor = bgColor.lighter(110);

    painter->setBrush(bgColor);
    painter->drawRect(rect());

    painter->restore();
}

void WelcomeButton::drawText(QPainter *painter)
{
    painter->save();

    const auto text = this->text();

    const auto fm = fontMetrics();

    const auto baseWidth  = width();
    const auto baseHeight = height();

    const auto textWidth  = fm.horizontalAdvance(text);
    const auto textHeight = fm.ascent();

    const auto x = baseWidth / 2 - textWidth / 2;
    const auto y = baseHeight / 2 + textHeight / 2;

    painter->setPen(textColor_);
    painter->drawText(x, y, text);

    painter->restore();
}

QColor WelcomeButton::backgroundColor() const
{
    return backgroundColor_;
}

void WelcomeButton::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (backgroundColor_ == newBackgroundColor)
        return;
    backgroundColor_ = newBackgroundColor;
    update();
    emit backgroundColorChanged();
}

double WelcomeButton::cornerRadius() const
{
    return cornerRadius_;
}

void WelcomeButton::setCornerRadius(double newCornerRadius)
{
    cornerRadius_ = newCornerRadius;
}


