#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QObject>
#include <QThread>
#include <QVector>

class ThreadPool : public QObject
{
    Q_OBJECT
public:
    explicit ThreadPool(QObject *parent = nullptr, int numberOfThreads = QThread::idealThreadCount());
    ~ThreadPool();

signals:

public slots:
    void moveObjectToLeastLoadedThread(QObject *object);

private:
    int indexOfLeastLoadedThread() const;

private:
    QVector<QThread *> threads_;
    QVector<QAtomicInt> threadLoads_;
};

#endif // THREADPOOL_H
