#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

class Message;

#include <QList>
#include <QDateTime>

class MessagesTable
{
public:
    static bool addOrUpdateMessage(const Message &message);

    static Message getMessageById(int id);

    static QList<Message> getUnsyncMessages(int userId, const QDateTime &lastUpdatedAt);

    static int lastInsertedId();

private:
    explicit MessagesTable() = default;

    static int lastInsertedId_;
};

#endif // MESSAGESTABLE_H
