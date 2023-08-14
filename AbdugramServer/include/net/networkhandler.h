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
    void removeSession(Session *session);

public:
    void sendLoginReply(Session *session, bool success, const User &user);
    void sendRegisterReply(Session *session, bool success, const User &user);
    void sendSyncUsersReply(Session *session, const QList<User> &unsyncUsers);
    void sendSyncChatsReply(Session *session, const QHash<Chat, QList<ChatUser>> &unsyncChats);
    void sendSyncMessagesReply(Session *session, const QList<Message> &unsyncMessages);
    void sendSearchReply(Session* session, const QList<User> &foundUsers);
    void sendCreateChatReply(int userId, const Chat &chat, const QList<User> &users, const QList<ChatUser> &chatUsers);
    void sendSendMessageReply(int userId, const Message &message);
    void sendLogoutReply(Session *session);

private:
    void send(int userId, const AbduMessagePtr &message);
    void send(Session* session, const AbduMessagePtr &message);

private:
    QHash<int, QList<Session *>> sessions_;

};

#endif // NETWORKHANDLER_H
