#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QHash>

#include <net_common/messages/abdumessage.h>

#include "threadpool.h"

class Session;
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

    void sendToClient(Session *client, const AbduMessagePtr &message);
    void sendToClient(int     userId,  const AbduMessagePtr &message);

protected:
    void incomingConnection(qintptr handle) override;

private:
    Session *createSession();

    void addSession(int id, Session *session);

private:
    ThreadPool *threadPool_ = nullptr;
    QHash<int, Session *> sessions_;
    friend class ServerMessageVisitor;
};

#endif // SERVER_H
