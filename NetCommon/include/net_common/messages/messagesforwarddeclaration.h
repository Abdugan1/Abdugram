#ifndef MESSAGESFORWARDDECLARATION_H
#define MESSAGESFORWARDDECLARATION_H

#include <QSharedDataPointer>

class AbduMessage;
class RegisterMessage;
class LoginMessage;
class LoginStatusMessage;
class RegisterStatusMessage;
class SyncChatsRequest;
class SearchOnServerMessage;
class SearchUsersResultMessage;
class CreateChatMessage;
class CreateChatResultMessage;

using AbduMessagePtr = QSharedDataPointer<AbduMessage>;
template<typename T>
using AnyMessagePtr = QSharedDataPointer<T>;

#endif // MESSAGESFORWARDDECLARATION_H
