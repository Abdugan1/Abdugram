#ifndef MESSAGESFORWARDDECLARATION_H
#define MESSAGESFORWARDDECLARATION_H

#include <QSharedDataPointer>

class AbduMessage;

class LoginMessage;
class RegisterMessage;
class SyncChatsRequest;
class SearchOnServerMessage;
class CreateChatMessage;
class SendMessageMessage;

class LoginStatusMessage;
class RegisterStatusMessage;
class SearchUsersResultMessage;
class CreateChatResultMessage;
class SendMessageResultMessage;

using AbduMessagePtr = QSharedDataPointer<AbduMessage>;
template<typename T>
using AnyMessagePtr = QSharedDataPointer<T>;

#endif // MESSAGESFORWARDDECLARATION_H
