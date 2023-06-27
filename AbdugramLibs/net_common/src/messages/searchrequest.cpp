#include "messages/searchrequest.h"
#include "messages/messagevisitor.h"

SearchRequest::SearchRequest()
    : AbduMessage{Type::SearchOnServer}
{

}

void SearchRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SearchRequest::getBodyData(DataStream *stream)
{
    *stream >> searchText_;
}

void SearchRequest::writeBodyData(DataStream *stream) const
{
    *stream << searchText_;
}

QString SearchRequest::searchText() const
{
    return searchText_;
}

void SearchRequest::setSearchText(const QString &newSearchText)
{
    searchText_ = newSearchText;
}
