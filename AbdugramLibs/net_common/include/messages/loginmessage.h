#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H

#include "abdumessage.h"

class NETCOMMON_EXPORT LoginMessage : public AbduMessage
{
public:
    explicit LoginMessage();

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

#endif // LOGINMESSAGE_H
