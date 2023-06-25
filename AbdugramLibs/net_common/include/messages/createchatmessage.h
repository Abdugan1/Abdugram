#ifndef CREATECHATMESSAGE_H
#define CREATECHATMESSAGE_H

#include "abdumessage.h"

#include <sql_common/data_structures/chat.h>

class ChatUser;

class NETCOMMON_EXPORT CreateChatMessage : public AbduMessage
{
public:
    explicit CreateChatMessage();

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

#endif // CREATECHATMESSAGE_H
