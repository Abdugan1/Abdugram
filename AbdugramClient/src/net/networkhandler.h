#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>

#include <net_common/messages/messagesforwarddeclaration.h>
#include <net_common/tcpsession.h>

class User;
class TcpSession;

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    static NetworkHandler *instance();

    QAbstractSocket::SocketState tcpState() const;

    bool isConnected() const;

signals:
    void connectedSucessfully();
    void connectionError();

    void loginSuccessfully();
    void registerSuccessfully();
    void searchResult(const QList<User> &usersSearchResult);

public slots:
    void connectToServer();
    void disconnectFromServer();

    void sendToServer(const AbduMessagePtr &message);

private slots:
    void onMessageReceived(const AbduMessagePtr &message);

private:
    explicit NetworkHandler(QObject *parent = nullptr);

    void emitLoginSuccessfully();
    void emitRegisterSuccessfully();
    void emitSearchResult(const QList<User> &usersSearchResult);

private:
    TcpSession *tcpSession_ = nullptr;

    friend class ClientMessageVisitor;
};

inline NetworkHandler *networkHandler()
{
    return NetworkHandler::instance();
}

#endif // NETWORKHANDLER_H
