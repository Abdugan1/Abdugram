#ifndef SEARCHREQUEST_H
#define SEARCHREQUEST_H

#include "abdumessage.h"

class NETCOMMON_EXPORT SearchRequest : public AbduMessage
{
public:
    explicit SearchRequest();

    void accept(MessageVisitor *visitor) const override;

    QString searchText() const;
    void setSearchText(const QString &newSearchText);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QString searchText_;
};

#endif // SEARCHREQUEST_H
