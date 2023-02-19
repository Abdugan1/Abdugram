#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

#include "threadpool.h"

class TcpSession;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

signals:
    void started();
    void stopped();
    void aboutToStop();

    void logCreated(const QString &log);

public slots:
    void start();
    void stop();
    void toggle();

protected:
    void incomingConnection(qintptr handle) override;

private:
    TcpSession *createSession();

private:
    ThreadPool threadPool_;
};

#endif // SERVER_H
