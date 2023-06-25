#include "ui/mv/founduserchatitem.h"

FoundUserChatItem::FoundUserChatItem()
{

}

int FoundUserChatItem::userId() const
{
    return userId_;
}

void FoundUserChatItem::setUserId(int newUserId)
{
    userId_ = newUserId;
}
