#include "abdumessagefactory.h"

#include "loginmessage.h"
#include "registermessage.h"

#include "loginstatusmessage.h"
#include "registerstatusmessage.h"

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
    case AbduMessage::Type::LoginStatus:
        abduMessage = new LoginStatusMessage;
        break;
    case AbduMessage::Type::RegisterStaus:
        abduMessage = new RegisterStatusMessage;
        break;
    default:
        abduMessage = AbduMessagePtr{};
        break;
    }

    if (abduMessage)
        abduMessage->fromData(data);

    return abduMessage;
}
