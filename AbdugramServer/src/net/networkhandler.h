#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QHash>

#include <net_common/messages/messagesforwarddeclaration.h>

class TcpSession;

class User;
class Chat;
class ChatUser;
class Message;

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);

    void addSession(int userId, TcpSession *session);

signals:
    void requestLoginReply(TcpSession* session, bool success, int userId);
    void requestRegisterReply(TcpSession* session, bool success, const User &user);
    void requestSyncUsersReply(TcpSession* session, const QList<User> &users);
    void requestSearchReply(TcpSession* session, const QList<User> &foundUsers);
    void requestCreateChatReply(int userId, const Chat &chat, const QList<ChatUser> &chatUsers);
    void requestSendMessageReply(int userId, const Message &message);

private slots:
    void sendLoginReply(TcpSession* session, bool success, int userId);
    void sendRegisterReply(TcpSession* session, bool success, const User &user);
    void sendSyncUsersReply(TcpSession* session, const QList<User> &users);
    void sendSearchReply(TcpSession* session, const QList<User> &foundUsers);
    void sendCreateChatReply(int userId, const Chat &chat, const QList<ChatUser> &chatUsers);
    void sendSendMessageReply(int userId, const Message &message);

private:
    void send(int userId, const AbduMessagePtr &message);
    void send(TcpSession* session, const AbduMessagePtr &message);

private:
    QHash<int, TcpSession *> sessions_;

};

#endif // NETWORKHANDLER_H
