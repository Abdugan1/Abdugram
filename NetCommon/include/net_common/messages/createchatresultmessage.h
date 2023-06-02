#ifndef CREATECHATRESULTMESSAGE_H
#define CREATECHATRESULTMESSAGE_H

#include "abdumessage.h"
#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/user.h>

class ChatUser;

class NETCOMMON_EXPORT CreateChatResultMessage : public AbduMessage
{
public:
    explicit CreateChatResultMessage();

    void accept(MessageVisitor *visitor) const override;

    Chat chat() const;
    void setChat(const Chat &newChat);

    QList<ChatUser> chatUsers() const;
    void setChatUsers(const QList<ChatUser> &newChatUsers);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    Chat chat_;
    QList<ChatUser> chatUsers_;
};

#endif // CREATECHATRESULTMESSAGE_H
