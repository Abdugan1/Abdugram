#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QHash>

#include <net_common/messages/abdumessage.h>

#include "threadpool.h"

class Session;
class NetworkHandler;
class ServerMessageVisitor;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    void connectToDatabase();

signals:
    void started();
    void stopped();
    void aboutToStop();

    void logCreated(const QString &log);

public slots:
    void start();
    void stop();
    void toggle();

private slots:
    void processMessage(const AbduMessagePtr &message);

    void onClientDisconected();

protected:
    void incomingConnection(qintptr handle) override;

private:
    Session *createSession();

private:
    ThreadPool *threadPool_ = nullptr;
    NetworkHandler *networkHandler_ = nullptr;
    friend class ServerMessageVisitor;
};

#endif // SERVER_H
