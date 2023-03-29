#include "rippleanimation.h"

#include <QApplication>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QWidget>
#include <QtMath>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QRegularExpression>
#include <QDebug>

inline double getDiagonal(const QRectF &rect)
{
    return std::sqrt(rect.width() * rect.width() + rect.height() * rect.height());
}

RippleAnimation::RippleAnimation(QWidget *parent)
    : QObject{parent}
{
    widget_ = parent;

    rippleWidthAnim_ = new QPropertyAnimation{this, "rippleWidth"};
    rippleWidthAnim_->setStartValue(0.0);
    rippleWidthAnim_->setEndValue(0.0);
    rippleWidthAnim_->setEasingCurve(QEasingCurve::OutQuad);

    appearOpacityAnim_ = new QPropertyAnimation{this, "opacity"};
    appearOpacityAnim_->setStartValue(0.0);
    appearOpacityAnim_->setEndValue(0.0);
    appearOpacityAnim_->setEasingCurve(QEasingCurve::OutQuad);

    disappearOpacityAnim_ = new QPropertyAnimation{this, "opacity"};
    disappearOpacityAnim_->setStartValue(0.0);
    disappearOpacityAnim_->setEndValue(0.0);
    disappearOpacityAnim_->setEasingCurve(QEasingCurve::OutQuad);

    connect(disappearOpacityAnim_, &QPropertyAnimation::finished, this, [this]() {
        setHasRipple(false);
    });

    QString styleSheet = qApp->styleSheet();
    QRegularExpression  borderRadiusRegExp(QString("%1\\s*\\{[^\\}]*border-radius\\s*:\\s*(\\d+)px\\s*;")
                                           .arg(widget_->metaObject()->className()));
    QRegularExpressionMatch match = borderRadiusRegExp.match(styleSheet);

    if (match.hasMatch())
        borderRadius_ = match.captured(1).toInt();
}

void RippleAnimation::start()
{
    rippleWidthAnim_->start();
    appearOpacityAnim_->start();
    setHasRipple(true);
}

void RippleAnimation::stop()
{
    disappearOpacityAnim_->start();
}

double RippleAnimation::rippleWidth() const
{
    return rippleWidth_;
}

void RippleAnimation::setRippleWidth(double newRippleWidth)
{
    if (qFuzzyCompare(rippleWidth_, newRippleWidth))
        return;
    rippleWidth_ = newRippleWidth;
    emit rippleWidthChanged();
}

double RippleAnimation::opacity() const
{
    return opacity_;
}

void RippleAnimation::setOpacity(double newRippleOpacity)
{
    if (qFuzzyCompare(opacity_, newRippleOpacity))
        return;
    opacity_ = newRippleOpacity;
    emit opacityChanged();
}

void RippleAnimation::setAppearTime(int msec)
{
    rippleWidthAnim_->setDuration(msec);
    appearOpacityAnim_->setDuration(msec);
}

void RippleAnimation::setDisappearTime(int msec)
{
    disappearOpacityAnim_->setDuration(msec);
}

void RippleAnimation::setEndRippleWidth(double endWidth)
{
    endRippleWidth_ = endWidth;
    rippleWidthAnim_->setEndValue(endRippleWidth_);
}

void RippleAnimation::setEndOpacity(double endOpacity)
{
    endOpacity_ = endOpacity;
    appearOpacityAnim_->setEndValue(endOpacity_);
    disappearOpacityAnim_->setStartValue(endOpacity_);
}

QColor RippleAnimation::color() const
{
    return color_;
}

void RippleAnimation::setColor(const QColor &newRippleColor)
{
    if (color_ == newRippleColor)
        return;
    color_ = newRippleColor;
    emit colorChanged();
}

bool RippleAnimation::hasRipple() const
{
    return hasRipple_;
}

void RippleAnimation::setHasRipple(bool newHasRipple)
{
    if (hasRipple_ == newHasRipple)
        return;
    hasRipple_ = newHasRipple;
    emit hasRippleChanged();
}

QPoint RippleAnimation::startPos() const
{
    return startPos_;
}

void RippleAnimation::setStartPos(QPoint newStartPos)
{
    startPos_ = newStartPos;
}

bool RippleAnimation::eventFilter(QObject *watched, QEvent *event)
{
    QWidget *widget = qobject_cast<QWidget *>(watched);
    if (!widget && widget != widget_)
        return false;
    if (!widget->isEnabled())
        return false;

    // Start ripple animation on left button press
    if (event->type() == QEvent::MouseButtonPress) {
        auto mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->buttons() & Qt::LeftButton) {
            int diagonal = getDiagonal(widget->geometry());
            setEndRippleWidth(diagonal);
            setStartPos(mouseEvent->pos());
            start();
        }
    }

    // Stop ripple animation on left button release
    else if (event->type() == QEvent::MouseButtonRelease) {
        auto mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            stop();
        }
    }

    return false;
}

void RippleAnimation::drawRipple() const
{
    QPainter painter{widget_};

    // button is rounded. So set clipping
    QPainterPath path;
    path.addRoundedRect(widget_->rect(), borderRadius_, borderRadius_);

    painter.setClipPath(path);

    painter.setOpacity(opacity());
    painter.translate(startPos());
    painter.setPen(Qt::NoPen);
    painter.setBrush(color());

    double w = rippleWidth();
    painter.drawEllipse(-w, -w, w * 2.0, w * 2.0);
}

