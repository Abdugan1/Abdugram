#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

class Message;

#include "SqlServer_global.h"

#include <QList>
#include <QDateTime>

class SQLSERVER_EXPORT MessagesTable
{
public:
    static bool addMessage(const Message &message);

    static Message getMessageById(int id);

    static QList<Message> getUnsyncMessages(int userId, const QDateTime &lastUpdatedAt);

    static int lastInsertedId();

private:
    explicit MessagesTable() = default;

    static int lastInsertedId_;
};

#endif // MESSAGESTABLE_H
