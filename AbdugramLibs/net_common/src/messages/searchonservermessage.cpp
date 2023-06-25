#include "messages/searchonservermessage.h"
#include "messages/messagevisitor.h"

SearchOnServerMessage::SearchOnServerMessage()
    : AbduMessage{Type::SearchOnServer}
{

}

void SearchOnServerMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SearchOnServerMessage::getBodyData(DataStream *stream)
{
    *stream >> searchText_;
}

void SearchOnServerMessage::writeBodyData(DataStream *stream) const
{
    *stream << searchText_;
}

QString SearchOnServerMessage::searchText() const
{
    return searchText_;
}

void SearchOnServerMessage::setSearchText(const QString &newSearchText)
{
    searchText_ = newSearchText;
}
