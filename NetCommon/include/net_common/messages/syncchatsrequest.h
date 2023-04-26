#ifndef SYNCCHATSREQUEST_H
#define SYNCCHATSREQUEST_H

#include "abdumessage.h"
#include <QDateTime>

class SyncChatsRequest : public AbduMessage
{
public:
    explicit SyncChatsRequest();

    QString fromUsername() const;
    void setFromUsername(const QString &newFromUsername);

    QDateTime lastUpdate() const;
    void setLastUpdate(const QDateTime &newLastUpdate);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QString   fromUsername_;
    QDateTime lastUpdate_;

};

#endif // SYNCCHATSREQUEST_H
