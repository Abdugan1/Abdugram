#ifndef SENDMESSAGEREQUEST_H
#define SENDMESSAGEREQUEST_H

#include "abdumessage.h"

#include <sql_common/data_structures/message.h>

class NETCOMMON_EXPORT SendMessageRequest : public AbduMessage
{
public:
    explicit SendMessageRequest();

    Message message() const;
    void setMessage(const Message &newMessage);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    Message message_;
};

#endif // SENDMESSAGEREQUEST_H
