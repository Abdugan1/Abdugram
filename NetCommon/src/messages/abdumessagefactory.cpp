#include "messages/abdumessagefactory.h"

#include "messages/loginmessage.h"
#include "messages/registermessage.h"
#include "messages/syncusersmessage.h"
#include "messages/syncchatsrequest.h"
#include "messages/syncmessagesrequest.h"
#include "messages/searchonservermessage.h"
#include "messages/createchatmessage.h"
#include "messages/sendmessagemessage.h"

#include "messages/loginstatusmessage.h"
#include "messages/registerstatusmessage.h"
#include "messages/syncusersreply.h"
#include "messages/syncchatsreply.h"
#include "messages/syncmessagesreply.h"
#include "messages/searchusersresultmessage.h"
#include "messages/createchatresultmessage.h"
#include "messages/sendmessageresultmessage.h"

#include <QDebug>

AbduMessagePtr AbduMessageFactory::fromData(const QByteArray &data)
{
    AbduMessagePtr abduMessage;

    int type;
    DataStream stream(data);
    stream >> type;

    switch (static_cast<AbduMessage::Type>(type)) {
    case AbduMessage::Type::Login:
        abduMessage = new LoginMessage;
        break;
    case AbduMessage::Type::Register:
        abduMessage = new RegisterMessage;
        break;
    case AbduMessage::Type::SyncUsersMessage:
        abduMessage = new SyncUsersMessage;
        break;
    case AbduMessage::Type::SyncChatsRequest:
        abduMessage = new SyncChatsRequest;
        break;
    case AbduMessage::Type::SyncMessagesRequest:
        abduMessage = new SyncMessagesRequest;
        break;
    case AbduMessage::Type::SearchOnServer:
        abduMessage = new SearchOnServerMessage;
        break;
    case AbduMessage::Type::CreateChat:
        abduMessage = new CreateChatMessage;
        break;
    case AbduMessage::Type::SendMessage:
        abduMessage = new SendMessageMessage;
        break;

    case AbduMessage::Type::LoginStatus:
        abduMessage = new LoginStatusMessage;
        break;
    case AbduMessage::Type::RegisterStaus:
        abduMessage = new RegisterStatusMessage;
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
        abduMessage = new SearchUsersResultMessage;
        break;
    case AbduMessage::Type::CreateChatResult:
        abduMessage = new CreateChatResultMessage;
        break;
    case AbduMessage::Type::SendMessageResult:
        abduMessage = new SendMessageResultMessage;
        break;
    }

    if (abduMessage != nullptr)
        abduMessage->fromData(data);

    return abduMessage;
}
