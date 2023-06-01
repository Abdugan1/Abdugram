#ifndef CREATEPRIVATECHATRESULTMESSAGE_H
#define CREATEPRIVATECHATRESULTMESSAGE_H

#include "abdumessage.h"
#include <sql_common/data_structures/user.h>

class NETCOMMON_EXPORT CreatePrivateChatResultMessage : public AbduMessage
{
public:
    explicit CreatePrivateChatResultMessage();

    int chatId() const;
    void setChatId(int newChatId);

    void accept(MessageVisitor *visitor) const override;

    User secondParticipiant() const;
    void setSecondParticipiant(const User &newSecondParticipiant);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    int  chatId_ =  -1;
    User secondParticipiant_;
};

#endif // CREATEPRIVATECHATRESULTMESSAGE_H
