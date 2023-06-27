#ifndef CREATECHATREPLY_H
#define CREATECHATREPLY_H

#include "abdumessage.h"

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/chat.h>

class NETCOMMON_EXPORT CreateChatReply : public AbduMessage
{
public:
    explicit CreateChatReply();

    void accept(MessageVisitor *visitor) const override;

    Chat chat() const;
    void setChat(const Chat &newChat);

    QList<ChatUser> chatUsers() const;
    void setChatUsers(const QList<ChatUser> &newChatUsers);

    QList<User> users() const;
    void setUsers(const QList<User> &newUsers);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    Chat chat_;
    QList<User> users_;
    QList<ChatUser> chatUsers_;
};

#endif // CREATECHATREPLY_H
