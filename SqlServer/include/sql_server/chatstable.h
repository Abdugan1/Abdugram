#ifndef CHATSTABLE_H
#define CHATSTABLE_H

//#include <data_structures/chat.h>

#include <QList>
#include <QDateTime>

class Chat;

class ChatsTable
{
public:
    static QList<Chat> getNewChatsWhereUserIsParticipiant(const QString &username,
                                                          const QDateTime &lastUpdate);
};

#endif // CHATSTABLE_H
