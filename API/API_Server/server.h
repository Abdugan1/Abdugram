#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

signals:
    void started();
    void stopped();

public slots:
    void start();
    void stop();

protected:
    void incomingConnection(qintptr handle) override;

private:
};

#endif // SERVER_H
