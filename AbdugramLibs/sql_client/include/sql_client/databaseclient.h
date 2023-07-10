#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H

#include "SqlClient_global.h"

#include <QObject>
#include <QList>

class User;
class Chat;
class ChatUser;
class Message;

class SQLCLIENT_EXPORT DatabaseClient : public QObject
{
    Q_OBJECT
public:
    enum class Tables {
        Users,
        Chats,
        ChatUsers,
        Messages,
    };

    static DatabaseClient *instance();

    void connectToDatabase(int ownId);

    QDateTime getLastUpdatedAt(Tables table);

    // Users
    bool addOrUpdateUser(const User &user);
    User getUserById(int userId);

    // Chats
    bool addOrUpdateChat(const Chat &chat);
    bool addChat(Chat chat, const QList<ChatUser> &chatUsers, int ownUserId);
    QList<Chat> getAllChats();

    // Messages
    bool addOrUpdateMessage(const Message &message);
    QList<Message> getMessages(int chatId);

    // ChatUsers
    bool addOrUpdateChatUser(const ChatUser &chatUser);

signals:
    void connected();

    void userAdded(const User &user);
    void chatAdded(const Chat &chat);
    void messageAdded(const Message &message);

protected:
    void createTables();
};

inline DatabaseClient *database()
{
    return DatabaseClient::instance();
}

#endif // DATABASECLIENT_H
