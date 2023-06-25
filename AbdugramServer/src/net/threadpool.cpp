#include "net/threadpool.h"

#include <cmath>
#include <QDebug>

ThreadPool::ThreadPool(QObject *parent, int numberOfThreads)
    : QObject{parent}
{
    threads_.resize(numberOfThreads);
    threadLoads_.resize(numberOfThreads);
    for (int i = 0; i < numberOfThreads; ++i) {
        QThread *thread = new QThread{this};
        thread->start();
        threads_[i] = thread;
    }
}

ThreadPool::~ThreadPool()
{
    for (auto* thread : threads_)
        thread->quit();

    for (auto* thread : threads_)
        thread->wait();
}

void ThreadPool::moveObjectToLeastLoadedThread(QObject *object)
{
    int threadIndex = indexOfLeastLoadedThread();
    ++threadLoads_[threadIndex];

    connect(object, &QObject::destroyed, this, [this, threadIndex]() {
        --threadLoads_[threadIndex];
    });

    QThread *thread = threads_[threadIndex];
    connect(thread, &QThread::finished, object, &QObject::deleteLater);

    object->moveToThread(thread);
}

int ThreadPool::indexOfLeastLoadedThread() const
{
    int minIndex = 0;
    for (int i = 1, size = threads_.size(); i < size; i++)  {
        if (threadLoads_.at(i) < threadLoads_.at(minIndex))
            minIndex = i;
    }

    return minIndex;
}
