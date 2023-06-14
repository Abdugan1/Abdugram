#ifndef SENDMESSAGERESULTMESSAGE_H
#define SENDMESSAGERESULTMESSAGE_H

#include "abdumessage.h"

#include <sql_common/data_structures/message.h>

class NETCOMMON_EXPORT SendMessageResultMessage : public AbduMessage
{
public:
    explicit SendMessageResultMessage();

    Message message() const;
    void setMessage(const Message &newMessage);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    Message message_;
};

#endif // SENDMESSAGERESULTMESSAGE_H
