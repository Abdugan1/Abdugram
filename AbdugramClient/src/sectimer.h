#ifndef SECTIMER_H
#define SECTIMER_H

#include <QObject>

class QTimer;

class SecTimer : public QObject
{
    Q_OBJECT
public:
    explicit SecTimer(QObject *parent = nullptr);

    void setDuration(int duration);

    void start();
    void stop();

signals:
    void started();
    void stopped();
    void timeout1Sec(int remaining);

private:
    QTimer *timer_ = nullptr;
    int duration_ = 0;
    int elapsed_  = 0;

};

#endif // SECTIMER_H
