#include "messages/abdumessagefactory.h"

#include "messages/loginrequest.h"
#include "messages/registerrequest.h"
#include "messages/syncusersrequest.h"
#include "messages/syncchatsrequest.h"
#include "messages/syncmessagesrequest.h"
#include "messages/searchrequest.h"
#include "messages/createchatrequest.h"
#include "messages/sendmessagerequest.h"
#include "messages/logoutrequest.h"
#include "messages/createprivatechatrequest.h"
#include "messages/messagereadrequest.h"
#include "messages/syncmessagereadsrequest.h"
#include "messages/isusernamefreerequest.h"

#include "messages/loginreply.h"
#include "messages/registerreply.h"
#include "messages/syncusersreply.h"
#include "messages/syncchatsreply.h"
#include "messages/syncmessagesreply.h"
#include "messages/searchusersreply.h"
#include "messages/createchatreply.h"
#include "messages/sendmessagereply.h"
#include "messages/logoutreply.h"
#include "messages/messagereadreply.h"
#include "messages/syncmessagereadsreply.h"
#include "messages/messagesupdated.h"
#include "messages/isusernamefreereply.h"

#include <QDebug>

AbduMessagePtr AbduMessageFactory::fromData(const QByteArray &data)
{
    AbduMessagePtr abduMessage;

    int type;
    DataStream stream(data);
    stream >> type;

    switch (static_cast<AbduMessage::Type>(type)) {
    case AbduMessage::Type::LoginRequest:
        abduMessage = new LoginRequest;
        break;
    case AbduMessage::Type::RegisterRequest:
        abduMessage = new RegisterRequest;
        break;
    case AbduMessage::Type::SyncUsersRequest:
        abduMessage = new SyncUsersRequest;
        break;
    case AbduMessage::Type::SyncChatsRequest:
        abduMessage = new SyncChatsRequest;
        break;
    case AbduMessage::Type::SyncMessagesRequest:
        abduMessage = new SyncMessagesRequest;
        break;
    case AbduMessage::Type::SearchOnServerRequest:
        abduMessage = new SearchRequest;
        break;
    case AbduMessage::Type::CreateChatRequest:
        abduMessage = new CreateChatRequest;
        break;
    case AbduMessage::Type::SendMessageRequest:
        abduMessage = new SendMessageRequest;
        break;
    case AbduMessage::Type::LogoutRequest:
        abduMessage = new LogoutRequest;
        break;
    case AbduMessage::Type::CreatePrivateChatRequest:
        abduMessage = new CreatePrivateChatRequest;
        break;
    case AbduMessage::Type::MessageReadRequest:
        abduMessage = new MessageReadRequest;
        break;
    case AbduMessage::Type::SyncMessageReadsRequest:
        abduMessage = new SyncMessageReadsRequest;
        break;
    case AbduMessage::Type::IsUsernameFreeRequest:
        abduMessage = new IsUsernameFreeRequest;
        break;

    case AbduMessage::Type::LoginReply:
        abduMessage = new LoginReply;
        break;
    case AbduMessage::Type::RegisterReply:
        abduMessage = new RegisterReply;
        break;
    case AbduMessage::Type::SyncUsersReply:
        abduMessage = new SyncUsersReply;
        break;
    case AbduMessage::Type::SyncChatsReply:
        abduMessage = new SyncChatsReply;
        break;
    case AbduMessage::Type::SyncMessagesReply:
        abduMessage = new SyncMessagesReply;
        break;
    case AbduMessage::Type::SearchUsersReply:
        abduMessage = new SearchUsersReply;
        break;
    case AbduMessage::Type::CreateChatResult:
        abduMessage = new CreateChatReply;
        break;
    case AbduMessage::Type::SendMessageResult:
        abduMessage = new SendMessageReply;
        break;
    case AbduMessage::Type::LogoutReply:
        abduMessage = new LogoutReply;
        break;
    case AbduMessage::Type::MessageReadReply:
        abduMessage = new MessageReadReply;
        break;
    case AbduMessage::Type::SyncMessageReadsReply:
        abduMessage = new SyncMessageReadsReply;
        break;
    case AbduMessage::Type::MessagesUpdated:
        abduMessage = new MessagesUpdated;
        break;
    case AbduMessage::Type::IsUsernameFreeReply:
        abduMessage = new IsUsernameFreeReply;
        break;
    }

    if (abduMessage != nullptr)
        abduMessage->fromData(data);

    return abduMessage;
}
