#ifndef MESSAGESUPDATED_H
#define MESSAGESUPDATED_H

#include "abdumessage.h"

#include <QList>

class Message;

class NETCOMMON_EXPORT MessagesUpdated : public AbduMessage
{
public:
    explicit MessagesUpdated();

    void accept(MessageVisitor *visitor) const override;

    QList<Message> messages() const;
    void setMessages(const QList<Message> &newMessages);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QList<Message> messages_;
};

#endif // MESSAGESUPDATED_H
