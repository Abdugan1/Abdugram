#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include "SqlServer_global.h"

#include <QDateTime>

class User;
class Chat;
class ChatUser;
class Message;
class MessageRead;

class SQLSERVER_EXPORT DatabaseServer
{
public:
    enum class Tables {
        Users,
        Chats,
        ChatUsers,
        Messages,
        MessageReads
    };

    static DatabaseServer *instance();

    void connectToDatabase();

    // Users
    bool        isUsernameExists(const QString &username);
    bool        isUserExists(const QString &username, const QString &password);
    bool        addUser(const User &user, const QString &password);
    int         getUserIdByUsername(const QString &username);
    User        getUserById(int userId);
    QList<User> getUsersByLikeSearch(const QString &likeSearch, int ownId);
    QList<User> getUnsyncUsers(int userId, const QDateTime &lastUpdatedAt);


    // Chats
    bool        addChat(const Chat &chat, const QList<ChatUser> &chatUsers);
    Chat        getChatById(int id);
    QList<Chat> getUnsyncChats(int userId, const QDateTime &lastUpdatedAt);


    // ChatUsers
    QList<ChatUser> getChatUsers(int chatId);
    QList<ChatUser> getUnsyncChatUsers(int userId, int chatId, const QDateTime &lastUpdatedAt);


    // Messages
    bool           addMessage(const Message &message);
    Message        getMessageById(int id);
    QList<Message> getUnsyncMessages(int userId, const QDateTime &lastUpdatedAt);
    bool           setIsReadOfMessageToTrue(int messageId);

    // MessageReads
    bool               addMessageReads(const QList<MessageRead> &messageReads);
    QList<MessageRead> getUnsyncMessageReads(int userId, const QDateTime &lastUpdatedAt);

    // Common
    int lastInsertedId(Tables table);

    //
    int getCountOfMessageReadsOfSpecificMessage(int messageId);

protected:
    void createTables();
};

inline DatabaseServer *database() {
    return DatabaseServer::instance();
}

#endif // DATABASESERVER_H
