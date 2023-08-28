#ifndef MESSAGESFORWARDDECLARATION_H
#define MESSAGESFORWARDDECLARATION_H

#include <QSharedDataPointer>

class AbduMessage;

class LoginRequest;
class RegisterRequest;
class SyncUsersRequest;
class SyncChatsRequest;
class SyncMessagesRequest;
class SearchRequest;
class CreateChatRequest;
class SendMessageRequest;
class LogoutRequest;
class CreatePrivateChatRequest;
class MessageReadRequest;
class SyncMessageReadsRequest;
class IsUsernameFreeRequest;

class LoginReply;
class RegisterReply;
class SyncUsersReply;
class SyncChatsReply;
class SyncMessagesReply;
class SearchUsersReply;
class CreateChatReply;
class SendMessageReply;
class LogoutReply;
class MessageReadReply;
class SyncMessageReadsReply;
class MessagesUpdated;
class IsUsernameFreeReply;

using AbduMessagePtr = QSharedDataPointer<AbduMessage>;
template<typename T>
using AnyMessagePtr = QSharedDataPointer<T>;

#endif // MESSAGESFORWARDDECLARATION_H
