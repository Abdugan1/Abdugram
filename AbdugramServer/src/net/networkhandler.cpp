#include "net/networkhandler.h"
#include "net/session.h"

#include <net_common/messages/loginreply.h>
#include <net_common/messages/registerreply.h>
#include <net_common/messages/syncusersreply.h>
#include <net_common/messages/syncchatsreply.h>
#include <net_common/messages/syncmessagesreply.h>
#include <net_common/messages/searchusersreply.h>
#include <net_common/messages/createchatreply.h>
#include <net_common/messages/sendmessagereply.h>
#include <net_common/messages/logoutreply.h>

#include <QDebug>

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}
{
    connect(this, &NetworkHandler::requestLoginReply, this, &NetworkHandler::sendLoginReply);
    connect(this, &NetworkHandler::requestRegisterReply, this, &NetworkHandler::sendRegisterReply);
    connect(this, &NetworkHandler::requestSyncUsersReply, this, &NetworkHandler::sendSyncUsersReply);
    connect(this, &NetworkHandler::requestSyncChatsReply, this, &NetworkHandler::sendSyncChatsReply);
    connect(this, &NetworkHandler::requestSyncMessagesReply, this, &NetworkHandler::sendSyncMessagesReply);
    connect(this, &NetworkHandler::requestSearchReply, this, &NetworkHandler::sendSearchReply);
    connect(this, &NetworkHandler::requestCreateChatReply, this, &NetworkHandler::sendCreateChatReply);
    connect(this, &NetworkHandler::requestSendMessageReply, this, &NetworkHandler::sendSendMessageReply);
    connect(this, &NetworkHandler::requestLogoutReply, this, &NetworkHandler::sendLogoutReply);
}

void NetworkHandler::addSession(int userId, Session *session)
{
    session->setUserId(userId);
    sessions_.insert(userId, session);
}

void NetworkHandler::removeSession(int userId)
{
    sessions_.remove(userId);
}

void NetworkHandler::sendLoginReply(Session* session, bool success, const User &user)
{
    AnyMessagePtr<LoginReply> loginReply{new LoginReply};
    loginReply->setSuccess(success);
    loginReply->setUserId(user.id());

    send(session, static_cast<AbduMessagePtr>(loginReply));
}

void NetworkHandler::sendRegisterReply(Session* session, bool success, const User &user)
{
    AnyMessagePtr<RegisterReply> registerReply{new RegisterReply};
    registerReply->setSuccess(success);
    registerReply->setUserId(user.id());

    send(session, static_cast<AbduMessagePtr>(registerReply));
}

void NetworkHandler::sendSyncUsersReply(Session* session, const QList<User> &users)
{
    AnyMessagePtr<SyncUsersReply> syncUsersReply{new SyncUsersReply};
    syncUsersReply->setUsers(users);

    send(session, static_cast<AbduMessagePtr>(syncUsersReply));
}

void NetworkHandler::sendSyncChatsReply(Session *session, const QHash<Chat, QList<ChatUser> > &unsyncChats)
{
    AnyMessagePtr<SyncChatsReply> syncChatsReply{new SyncChatsReply};
    syncChatsReply->setUnsyncChats(unsyncChats);

    send(session, static_cast<AbduMessagePtr>(syncChatsReply));
}

void NetworkHandler::sendSyncMessagesReply(Session *session, const QList<Message> &unsyncMessages)
{
    AnyMessagePtr<SyncMessagesReply> syncMessagesReply{new SyncMessagesReply};
    syncMessagesReply->setUnsyncMessages(unsyncMessages);

    send(session, static_cast<AbduMessagePtr>(syncMessagesReply));
}

void NetworkHandler::sendSearchReply(Session* session, const QList<User> &foundUsers)
{
    AnyMessagePtr<SearchUsersReply> searchReply{new SearchUsersReply};
    searchReply->setUsers(foundUsers);

    send(session, static_cast<AbduMessagePtr>(searchReply));
}

void NetworkHandler::sendCreateChatReply(int userId, const Chat &chat, const QList<User> &users, const QList<ChatUser> &chatUsers)
{
    AnyMessagePtr<CreateChatReply> createChatReply{new CreateChatReply};
    createChatReply->setChat(chat);
    createChatReply->setUsers(users);
    createChatReply->setChatUsers(chatUsers);

    send(userId, static_cast<AbduMessagePtr>(createChatReply));
}

void NetworkHandler::sendSendMessageReply(int userId, const Message &message)
{
    AnyMessagePtr<SendMessageReply> sendMessageReply{new SendMessageReply};
    sendMessageReply->setMessage(message);

    send(userId, static_cast<AbduMessagePtr>(sendMessageReply));
}

void NetworkHandler::sendLogoutReply(Session *session)
{
    AnyMessagePtr<LogoutReply> logoutReply{new LogoutReply};

    send(session, static_cast<AbduMessagePtr>(logoutReply));
}

void NetworkHandler::send(int userId, const AbduMessagePtr &message)
{
    if (!sessions_.contains(userId))
        return;

    sessions_[userId]->send(message);
}

void NetworkHandler::send(Session *session, const AbduMessagePtr &message)
{
    session->send(message);
}
