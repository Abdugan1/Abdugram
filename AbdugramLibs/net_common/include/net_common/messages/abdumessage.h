#ifndef ABDUMESSAGE_H
#define ABDUMESSAGE_H

#include "../NetCommon_global.h"

#include <QString>
#include <QMetaType>
#include "../datastream.h"
#include "messagesforwarddeclaration.h"

class MessageVisitor;

class NETCOMMON_EXPORT AbduMessage : public QSharedData
{
public:
    // !!!Add new types to end for version independent!!!
    enum class Type : int {
        Unknown = -1,

        ClientSide = 0,
        LoginRequest = ClientSide + 1,
        RegisterRequest,
        SyncUsersRequest,
        SyncChatsRequest,
        SyncChatUsersRequest,
        SyncMessagesRequest,
        SearchOnServerRequest,
        CreateChatRequest,
        SendMessageRequest,
        LogoutRequest,
        CreatePrivateChatRequest,
        MessageReadRequest,
        SyncMessageReadsRequest,
        IsUsernameFreeRequest,

        ServerSide = 1000000000,
        LoginReply = ServerSide + 1,
        RegisterReply,
        SyncUsersReply,
        SyncChatsReply,
        SyncChatUsersReply,
        SyncMessagesReply,
        SearchUsersReply,
        CreateChatResult,
        SendMessageResult,
        LogoutReply,
        MessageReadReply,
        SyncMessageReadsReply,
        MessagesUpdated,
        IsUsernameFreeReply,
    };

public:
    explicit AbduMessage(Type type);
    virtual ~AbduMessage();

    Type type() const;

    //! Sets data info to class
    //! Base class implementation just skips type
    void fromData(const QByteArray &data);

    //! Constructs QByteArray from class
    //! Base class implementation writes type to it
    QByteArray toData() const;

    //! Returns occupied bytes count for header
    int headerSize() const;

    virtual void accept(MessageVisitor *visitor) const;

protected:
    virtual void getBodyData(DataStream *stream);
    virtual void writeBodyData(DataStream *stream) const;

private:
    void getHeaderData(DataStream *stream);
    void writeHeaderData(DataStream *stream) const;

private:
    Type type_;
};

Q_DECLARE_METATYPE(AbduMessagePtr)

#endif // ABDUMESSAGE_H
