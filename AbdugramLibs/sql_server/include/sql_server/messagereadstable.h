#ifndef MESSAGEREADSTABLE_H
#define MESSAGEREADSTABLE_H

#include <QList>

class QDateTime;

class MessageRead;

class MessageReadsTable
{
public:
    static bool addMessageReads(const MessageRead &messageRead);

    static QList<MessageRead> getUnsyncMessageReads(int userId, const QDateTime &lastUpdatedAt);

private:
    explicit MessageReadsTable();

    static int lastInsertedId_;
};

#endif // MESSAGEREADSTABLE_H
