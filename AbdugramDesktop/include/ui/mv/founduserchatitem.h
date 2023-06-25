#ifndef FOUNDUSERCHATITEM_H
#define FOUNDUSERCHATITEM_H

#include "chatitem.h"

class FoundUserChatItem : public ChatItem
{
public:
    explicit FoundUserChatItem();
    ~FoundUserChatItem() = default;

    int userId() const;
    void setUserId(int newUserId);

private:
    int userId_ = -1;
};

#endif // FOUNDUSERCHATITEM_H
