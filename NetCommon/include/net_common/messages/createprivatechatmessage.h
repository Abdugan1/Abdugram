#ifndef CREATEPRIVATECHATMESSAGE_H
#define CREATEPRIVATECHATMESSAGE_H

#include "abdumessage.h"

class NETCOMMON_EXPORT CreatePrivateChatMessage : public AbduMessage
{
public:
    explicit CreatePrivateChatMessage();

    void accept(MessageVisitor *visitor) const override;

    int user1Id() const;
    void setUser1Id(int newUser1Id);

    int user2Id() const;
    void setUser2Id(int newUser2Id);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    int user1Id_;
    int user2Id_;

};

#endif // CREATEPRIVATECHATMESSAGE_H
