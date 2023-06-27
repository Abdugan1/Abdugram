#include "messages/abdumessagefactory.h"

#include "messages/loginrequest.h"
#include "messages/registerrequest.h"
#include "messages/syncusersrequest.h"
#include "messages/syncchatsrequest.h"
#include "messages/syncmessagesrequest.h"
#include "messages/searchrequest.h"
#include "messages/createchatrequest.h"
#include "messages/sendmessagerequest.h"

#include "messages/loginreply.h"
#include "messages/registerreply.h"
#include "messages/syncusersreply.h"
#include "messages/syncchatsreply.h"
#include "messages/syncmessagesreply.h"
#include "messages/searchusersreply.h"
#include "messages/createchatreply.h"
#include "messages/sendmessagereply.h"

#include <QDebug>

AbduMessagePtr AbduMessageFactory::fromData(const QByteArray &data)
{
    AbduMessagePtr abduMessage;

    int type;
    DataStream stream(data);
    stream >> type;

    switch (static_cast<AbduMessage::Type>(type)) {
    case AbduMessage::Type::Login:
        abduMessage = new LoginRequest;
        break;
    case AbduMessage::Type::Register:
        abduMessage = new RegisterRequest;
        break;
    case AbduMessage::Type::SyncUsersMessage:
        abduMessage = new SyncUsersRequest;
        break;
    case AbduMessage::Type::SyncChatsRequest:
        abduMessage = new SyncChatsRequest;
        break;
    case AbduMessage::Type::SyncMessagesRequest:
        abduMessage = new SyncMessagesRequest;
        break;
    case AbduMessage::Type::SearchOnServer:
        abduMessage = new SearchRequest;
        break;
    case AbduMessage::Type::CreateChat:
        abduMessage = new CreateChatRequest;
        break;
    case AbduMessage::Type::SendMessage:
        abduMessage = new SendMessageRequest;
        break;

    case AbduMessage::Type::LoginStatus:
        abduMessage = new LoginReply;
        break;
    case AbduMessage::Type::RegisterStaus:
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
    case AbduMessage::Type::SearchUsersResult:
        abduMessage = new SearchUsersReply;
        break;
    case AbduMessage::Type::CreateChatResult:
        abduMessage = new CreateChatReply;
        break;
    case AbduMessage::Type::SendMessageResult:
        abduMessage = new SendMessageReply;
        break;
    }

    if (abduMessage != nullptr)
        abduMessage->fromData(data);

    return abduMessage;
}
