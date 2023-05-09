#ifndef CHATSTABLE_H
#define CHATSTABLE_H

#include "SqlClient_global.h"

class SQLCLIENT_EXPORT ChatsTable
{
public:
    static bool isChatExist(const QString &chatName);
};

#endif // CHATSTABLE_H
