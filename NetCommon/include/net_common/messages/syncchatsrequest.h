#ifndef SYNCCHATSREQUEST_H
#define SYNCCHATSREQUEST_H

#include "abdumessage.h"

class SyncChatsRequest : public AbduMessage
{
public:
    explicit SyncChatsRequest();

    QString fromUsername() const;
    void setFromUsername(const QString &newFromUsername);

    QString lastUpdate() const;
    void setLastUpdate(const QString &newLastUpdate);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QString fromUsername_;
    QString lastUpdate_;

};

#endif // SYNCCHATSREQUEST_H
