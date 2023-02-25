#include "sectimer.h"

#include <QTimer>

SecTimer::SecTimer(QObject *parent)
    : QObject{parent}
    , timer_{new QTimer{this}}
{
    timer_->setSingleShot(false);
    timer_->setInterval(1000);

    connect(timer_, &QTimer::timeout, this, [this]() {
        emit timeout1Sec(duration_ - (++elapsed_));
        if (elapsed_ == duration_)
            stop();
    });
}

void SecTimer::setDuration(int duration)
{
    duration_ = duration;
}

void SecTimer::start()
{
    elapsed_ = 0;
    timer_->start();
    emit started();
}

void SecTimer::stop()
{
    elapsed_ = 0;
    timer_->stop();
    emit stopped();
}
