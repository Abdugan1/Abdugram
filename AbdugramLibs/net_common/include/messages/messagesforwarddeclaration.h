#ifndef MESSAGESFORWARDDECLARATION_H
#define MESSAGESFORWARDDECLARATION_H

#include <QSharedDataPointer>

class AbduMessage;

class LoginMessage;
class RegisterMessage;
class SyncUsersMessage;
class SyncChatsRequest;
class SyncMessagesRequest;
class SearchOnServerMessage;
class CreateChatMessage;
class SendMessageMessage;


class LoginStatusMessage;
class RegisterStatusMessage;
class SyncUsersReply;
class SyncChatsReply;
class SyncMessagesReply;
class SearchUsersResultMessage;
class CreateChatResultMessage;
class SendMessageResultMessage;


using AbduMessagePtr = QSharedDataPointer<AbduMessage>;
template<typename T>
using AnyMessagePtr = QSharedDataPointer<T>;

#endif // MESSAGESFORWARDDECLARATION_H
