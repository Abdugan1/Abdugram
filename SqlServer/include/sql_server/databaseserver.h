#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include "SqlServer_global.h"

#include <QDateTime>

class User;
class Chat;
class ChatUser;
class Message;

class SQLSERVER_EXPORT DatabaseServer
{
public:
    enum class Tables {
        Users,
        Chats,
        ChatUsers,
        Messages
    };

    static DatabaseServer *instance();

    void connectToDatabase();

    // Users
    bool        isUsernameExists(const QString &username);
    bool        isUserExists(const QString &username, const QString &password);
    bool        addUser(const User &user, const QString &password);
    int         getUserIdByUsername(const QString &username);
    User        getUserById(int userId);
    QList<User> getUsersByLikeSearch(const QString &likeSearch);
    QList<User> getUpdatedUsersForUser(int userId, const QDateTime &lastUpdatedAt);


    // Chats
    bool addChat(const Chat &chat, const QList<ChatUser> &chatUsers);
    Chat getChatById(int id);


    // ChatUsers
    QList<ChatUser> getChatUsers(int chatId);


    // Messages
    bool addMessage(const Message &message);
    Message getMessageById(int id);

    // Common
    int lastInsertedId(Tables table);

protected:
    void createTables();
};

inline DatabaseServer *database() {
    return DatabaseServer::instance();
}

#endif // DATABASESERVER_H
