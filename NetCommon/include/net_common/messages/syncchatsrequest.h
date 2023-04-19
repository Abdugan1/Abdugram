#ifndef SYNCCHATSREQUEST_H
#define SYNCCHATSREQUEST_H

#include "messages/abdumessage.h"

class SyncChatsRequest : public AbduMessage
{
public:
    explicit SyncChatsRequest();

    QString fromUsername() const;
    void setFromUsername(const QString &newFromUsername);

    QString lastUpdate() const;
    void setLastUpdate(const QString &newLastUpdate);

    QByteArray toData() const override;
    void accept(MessageVisitor *visitor) const override;

private:
    void gainDataFromPayload(DataStream *stream) override;

private:
    QString fromUsername_;
    QString lastUpdate_;

};

#endif // SYNCCHATSREQUEST_H
