#ifndef CHATSTABLE_H
#define CHATSTABLE_H

//#include <data_structures/chat.h>
#include "SqlServer_global.h"

#include "chatuserstable.h"

#include <QList>
#include <QDateTime>

class Chat;

class SQLSERVER_EXPORT ChatsTable
{
public:
    static QList<Chat> getNewChatsWhereUserIsParticipiant(const QString &username,
                                                          const QDateTime &lastUpdate);

    static Chat createPrivateChat(int user1, int user2);

    static int addChat(const Chat &chat);

    static Chat getChatById(int chatId);

private:
    explicit ChatsTable() = default;
};

#endif // CHATSTABLE_H
