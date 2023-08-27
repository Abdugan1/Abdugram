#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H

#include "SqlClient_global.h"

#include "data_structures/chatitem.h"

#include <sql_common/data_structures/message.h>

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
class MessageRead;


class SQLCLIENT_EXPORT DatabaseClient : public QObject
{
    Q_OBJECT
public:
    enum class Tables {
        Users,
        Chats,
        ChatUsers,
        Messages,
        MessageReads
    };

    static DatabaseClient *instance();

    std::shared_ptr<SqlDatabase> threadDb();

    int ownId() const;
    void setOwnId(int ownId);

    QDateTime getLastUpdatedAt(Tables table);

    // Users
    bool addOrUpdateBunchOfUsers(const QList<User> &users);
    bool addOrUpdateUser(const User &user);
    User getUserById(int userId);

    // Chats
    bool        addOrUpdateBunchOfChats(const QHash<Chat, QList<ChatUser> >& chats);
    bool        addOrUpdateChat(Chat chat, const QList<ChatUser> &chatUsers, int ownUserId);
    QList<Chat> getAllChats();

    // ChatsView
    QList<ChatViewItem> getChatsView();

    // Messages
    bool           addOrUpdateBunchOfMessages(const QList<Message> &messages);
    bool           addOrUpdateMessage(const Message &message);
    QList<Message> getMessages(int chatId);
    Message        getMessageById(int id);
    bool           updateMessages(const QList<Message> &messages);

    // ChatUsers
    bool addOrUpdateChatUser(const ChatUser &chatUser);

    // MessageReads
    bool addOrUpdateBunchOfMessageReads(const QList<MessageRead> &messageReads);

    //
    void likeSearch(const QString &likeSearch);

signals:
    void connected();

    void userAdded(const User &user);
    void chatAdded(const Chat &chat);
    void messageAdded(const Message &message);
    void messageReadAdded(const MessageRead &messageReads);
    void messagesUpdated(const QList<Message> &updatedMessages);
    
    void foundChats(const QList<ChatViewItem> &chatViews);

private:
    explicit DatabaseClient();

    // ChatsView
    QList<ChatViewItem> getChatsViewByLikeSearch(const QString &likeSearch);

private:
    int ownId_ = -1;

    QThreadStorage<std::shared_ptr<SqlDatabase>> threadDatabases_;

    QMutex users_;
    QMutex chats_;
    QMutex chatUsers_;
    QMutex chatsView_;
    QMutex messages_;
    QMutex messageReads_;
};

inline DatabaseClient *database()
{
    return DatabaseClient::instance();
}

#endif // DATABASECLIENT_H
