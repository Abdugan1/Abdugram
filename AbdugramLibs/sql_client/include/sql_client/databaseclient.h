#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H

#include "SqlClient_global.h"

#include <QObject>
#include <QList>
#include <QThreadStorage>
#include <QMutexLocker>

#include <memory>

class SqlQuery;

class SqlDatabase;
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

    std::shared_ptr<SqlDatabase> threadDb();

    int ownId() const;
    void setOwnId(int ownId);

    QDateTime getLastUpdatedAt(Tables table);

    // Users
    bool addOrUpdateUser(const User &user);
    User getUserById(int userId);

    // Chats
    bool addOrUpdateChat(const Chat &chat);
    bool addChat(Chat chat, const QList<ChatUser> &chatUsers, int ownUserId);
    QList<Chat> getAllChats();

    // ChatsView
    SqlQuery getChatsView();

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

private:
    explicit DatabaseClient();

    int ownId_ = -1;

    QThreadStorage<std::shared_ptr<SqlDatabase>> threadDatabases_;

    QMutex users_;
    QMutex chats_;
    QMutex chatUsers_;
    QMutex chatsView_;
    QMutex messages_;
};

inline DatabaseClient *database()
{
    return DatabaseClient::instance();
}

#endif // DATABASECLIENT_H
