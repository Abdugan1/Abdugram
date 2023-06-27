#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H

#include "abdumessage.h"

class NETCOMMON_EXPORT LoginRequest : public AbduMessage
{
public:
    explicit LoginRequest();

    QString username() const;
    void setUsername(const QString &newUsername);

    QString password() const;
    void setPassword(const QString &newPassword);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QString username_;
    QString password_;

};

#endif // LOGINREQUEST_H
