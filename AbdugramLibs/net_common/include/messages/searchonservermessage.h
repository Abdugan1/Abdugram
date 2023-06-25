#ifndef SEARCHONSERVERMESSAGE_H
#define SEARCHONSERVERMESSAGE_H

#include "abdumessage.h"

class NETCOMMON_EXPORT SearchOnServerMessage : public AbduMessage
{
public:
    explicit SearchOnServerMessage();

    void accept(MessageVisitor *visitor) const override;

    QString searchText() const;
    void setSearchText(const QString &newSearchText);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QString searchText_;
};

#endif // SEARCHONSERVERMESSAGE_H
