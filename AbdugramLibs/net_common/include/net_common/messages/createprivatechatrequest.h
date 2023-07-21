#ifndef CREATEPRIVATECHATREQUEST_H
#define CREATEPRIVATECHATREQUEST_H

#include "abdumessage.h"

#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>

class NETCOMMON_EXPORT CreatePrivateChatRequest : public AbduMessage
{
public:
    explicit CreatePrivateChatRequest();

    void accept(MessageVisitor *visitor) const override;

    Chat chat() const;
    void setChat(const Chat &newChat);

    QList<ChatUser> chatUsers() const;
    void setChatUsers(const QList<ChatUser> &newChatUsers);

    Message message() const;
    void setMessage(const Message &newMessage);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    Chat chat_;
    QList<ChatUser> chatUsers_;
    Message message_;
};

#endif // CREATEPRIVATECHATREQUEST_H
