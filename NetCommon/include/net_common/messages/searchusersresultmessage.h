#ifndef SEARCHUSERSRESULTMESSAGE_H
#define SEARCHUSERSRESULTMESSAGE_H

#include "abdumessage.h"

class User;

class NETCOMMON_EXPORT SearchUsersResultMessage : public AbduMessage
{
public:
    explicit SearchUsersResultMessage();

    void accept(MessageVisitor *visitor) const override;

    QList<User> users() const;
    void setUsers(const QList<User> &newUsers);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QList<User> users_;
};

#endif // SEARCHUSERSRESULTMESSAGE_H
