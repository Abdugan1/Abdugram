#ifndef MESSAGEREADSTABLE_H
#define MESSAGEREADSTABLE_H

#include "SqlClient_global.h"

class MessageRead;

class SQLCLIENT_EXPORT MessageReadsTable
{
public:
    static bool addOrUpdateMessageRead(const MessageRead &messageRead);

private:
    explicit MessageReadsTable();
};

#endif // MESSAGEREADSTABLE_H
