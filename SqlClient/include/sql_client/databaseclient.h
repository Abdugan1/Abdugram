#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H

#include "SqlClient_global.h"

#include <QObject>
#include <QList>

#include <sql_common/database.h>

class User;
class Chat;
class ChatUser;
class Message;

class SQLCLIENT_EXPORT DatabaseClient : public QObject, public Database
{
    Q_OBJECT
public:
    static DatabaseClient *instance();

    void connectToDatabase() override;

    // Users
    bool addOrIgnoreUser(const User &user);


    // Chats
    bool addChat(Chat chat, const QList<ChatUser> &chatUsers, int ownUserId);


    // Messages
    bool addMessage(const Message &message);
    QList<Message> getMessages(int chatId);

signals:
    void userAdded(const User &user);
    void chatAdded(const Chat &chat);
    void messageAdded(const Message &message);

protected:
    void createTables() override;
};

inline DatabaseClient *database()
{
    return DatabaseClient::instance();
}

#endif // DATABASECLIENT_H
