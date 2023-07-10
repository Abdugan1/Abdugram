#include "ui/stackedwidget.h"

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLayout>

StackedWidget::StackedWidget(QWidget *parent)
    : QStackedWidget{parent}
{
}

void StackedWidget::toWidget(QWidget *widget)
{
    toIndex(indexOf(widget));
}

void StackedWidget::toIndex(int index)
{
    currentWidget_ = widget(currentIndex());
    previousWidget_ = currentWidget_;
    toSlideWidget_ = widget(index);

    setupToSlideWidget();

    if (currentIndex() < index) {
        slideForward();
    } else {
        slideBackward();
    }

    currentWidget_ = toSlideWidget_;
}

void StackedWidget::startAnimation(const QPoint &currentBegin, const QPoint &currentEnd,
                                   const QPoint &toSlideBegin, const QPoint &toSlideEnd)
{
    QPropertyAnimation *currentAnim = new QPropertyAnimation{currentWidget_, "pos"};
    currentAnim->setStartValue(currentBegin);
    currentAnim->setEndValue(currentEnd);
    currentAnim->setDuration(slideDuration_);
    currentAnim->setEasingCurve(easingCurve_);

    QPropertyAnimation *toSlideAnim = new QPropertyAnimation{toSlideWidget_, "pos"};
    toSlideAnim->setStartValue(toSlideBegin);
    toSlideAnim->setEndValue(toSlideEnd);
    toSlideAnim->setDuration(slideDuration_);
    toSlideAnim->setEasingCurve(easingCurve_);

    QParallelAnimationGroup *animations = new QParallelAnimationGroup;
    animations->addAnimation(currentAnim);
    animations->addAnimation(toSlideAnim);

    connect(animations, &QParallelAnimationGroup::finished, this, [this]() {
        setCurrentWidget(toSlideWidget_);
        emit slideFinished();
    });

    animations->start(QAbstractAnimation::DeleteWhenStopped);
}

QWidget *StackedWidget::previousWidget()
{
    return previousWidget_;
}

void StackedWidget::slideBackward()
{
    QPoint currentBegin = currentWidget_->pos();
    QPoint currentEnd   = QPoint{currentBegin.x() + size().width(), currentBegin.y()};
    QPoint toSlideBegin = QPoint{currentBegin.x() - size().width(), currentBegin.y()};
    QPoint toSlideEnd   = currentBegin;

    startAnimation(currentBegin, currentEnd, toSlideBegin, toSlideEnd);
}

QEasingCurve StackedWidget::easingCurve() const
{
    return easingCurve_;
}

void StackedWidget::setEasingCurve(const QEasingCurve &newEasingCurve)
{
    easingCurve_ = newEasingCurve;
}

void StackedWidget::setupToSlideWidget()
{
    toSlideWidget_->resize(currentWidget_->size());
    toSlideWidget_->show();
    toSlideWidget_->raise();
}

void StackedWidget::slideForward()
{
    QPoint currentBegin = currentWidget_->pos();
    QPoint currentEnd   = QPoint{currentBegin.x() - size().width(), currentBegin.y()};
    QPoint toSlideBegin = QPoint{currentBegin.x() + size().width(), currentBegin.y()};
    QPoint toSlideEnd   = currentWidget_->pos();

    startAnimation(currentBegin, currentEnd, toSlideBegin, toSlideEnd);
}

int StackedWidget::slideDuration() const
{
    return slideDuration_;
}

void StackedWidget::setSlideDuration(int newSlideDuration)
{
    if (slideDuration_ == newSlideDuration)
        return;
    slideDuration_ = newSlideDuration;
}
