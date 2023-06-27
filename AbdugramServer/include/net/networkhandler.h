#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QHash>

#include <net_common/messages/messagesforwarddeclaration.h>

class Session;

class User;
class Chat;
class ChatUser;
class Message;

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);

    void addSession(int userId, Session *session);
    void removeSession(int userId);

signals:
    void requestLoginReply(Session *session, bool success, const User &user);
    void requestRegisterReply(Session *session, bool success, const User &user);
    void requestSyncUsersReply(Session *session, const QList<User> &unsyncUsers);
    void requestSyncChatsReply(Session *session, const QHash<Chat, QList<ChatUser>> &unsyncChats);
    void requestSyncMessagesReply(Session *session, const QList<Message> &unsyncMessages);
    void requestSearchReply(Session* session, const QList<User> &foundUsers);
    void requestCreateChatReply(int userId, const Chat &chat, const QList<User> &users, const QList<ChatUser> &chatUsers);
    void requestSendMessageReply(int userId, const Message &message);

private slots:
    void sendLoginReply(Session *session, bool success, const User &user);
    void sendRegisterReply(Session *session, bool success, const User &user);
    void sendSyncUsersReply(Session *session, const QList<User> &unsyncUsers);
    void sendSyncChatsReply(Session *session, const QHash<Chat, QList<ChatUser>> &unsyncChats);
    void sendSyncMessagesReply(Session *session, const QList<Message> &unsyncMessages);
    void sendSearchReply(Session* session, const QList<User> &foundUsers);
    void sendCreateChatReply(int userId, const Chat &chat, const QList<User> &users, const QList<ChatUser> &chatUsers);
    void sendSendMessageReply(int userId, const Message &message);

private:
    void send(int userId, const AbduMessagePtr &message);
    void send(Session* session, const AbduMessagePtr &message);

private:
    QHash<int, Session *> sessions_;

};

#endif // NETWORKHANDLER_H
