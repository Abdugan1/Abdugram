#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>

#include <net_common/messages/messagesforwarddeclaration.h>
#include <net_common/tcpsession.h>

class TcpSession;

class User;
class Chat;
class ChatUser;
class Message;

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    static NetworkHandler *instance();

    QAbstractSocket::SocketState tcpState() const;

    bool isConnected() const;

    int userId() const;

    QString lastUsername() const;
    QString lastPassword() const;

    void sendLoginRequest(const QString &username, const QString &password);

    void sendRegisterRequest(const QString &firstName,
                             const QString &username,
                             const QString &email,
                             const QString &phone,
                             const QString &password);

    void sendSearchRequest(const QString &searchText);

    void sendCreateChatRequest(const Chat &chat, const QList<ChatUser> &chatUsers);

    void sendSendMessageRequest(const Message &message);

    void sendSyncUsersRequest(const QDateTime &lastUpdate);

    void sendSyncChatsRequest(const QDateTime &chatsLastUpdate, const QDateTime &chatUsersLastUpdate);

    void sendSyncMessagesRequest(const QDateTime &lastUpdate);

    void sendLogoutRequest();

signals:
    void connectedSucessfully();
    void connectionError();

    void syncFinished();

    void loginResult(bool success);
    void registerResult(bool success);
    void loggedOut();

    void searchResult(const QList<User> &usersSearchResult);

public slots:
    void connectToServer();
    void disconnectFromServer();

private slots:
    void onMessageReceived(const AbduMessagePtr &message);

private:
    explicit NetworkHandler(QObject *parent = nullptr);

    void sendToServer(const AbduMessagePtr &message);

private:
    TcpSession *tcpSession_ = nullptr;
    int userId_ = 0;

    QString lastUsername_;
    QString lastPassword_;

    friend class ClientMessageVisitor;
};

inline NetworkHandler *networkHandler()
{
    return NetworkHandler::instance();
}

#endif // NETWORKHANDLER_H
