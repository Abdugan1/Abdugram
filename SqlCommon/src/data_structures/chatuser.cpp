#include "data_structures/chatuser.h"

#include <QSqlRecord>
#include <QVariant>
#include <QDataStream>
#include <QMap>

ChatUser::ChatUser()
{

}

int ChatUser::chatId() const
{
    return chatId_;
}

void ChatUser::setChatId(int newChatId)
{
    chatId_ = newChatId;
}

int ChatUser::userId() const
{
    return userId_;
}

void ChatUser::setUserId(int newUserId)
{
    userId_ = newUserId;
}

ChatUser::Role ChatUser::role() const
{
    return role_;
}

void ChatUser::setRole(Role newRole)
{
    role_ = newRole;
}

QDateTime ChatUser::joinedAt() const
{
    return joinedAt_;
}

void ChatUser::setJoinedAt(const QDateTime &newJoinedAt)
{
    joinedAt_ = newJoinedAt;
}

QDateTime ChatUser::leftAt() const
{
    return leftAt_;
}

void ChatUser::setLeftAt(const QDateTime &newLeftAt)
{
    leftAt_ = newLeftAt;
}

bool ChatUser::isValid() const
{
    return (chatId_ >= 0) && (userId_ >= 0);
}

QString ChatUser::roleToString(Role role)
{
    static const QMap<ChatUser::Role, QString> rolesToString = {
        {ChatUser::Role::Owner, "owner"},
        {ChatUser::Role::Admin, "admin"},
        {ChatUser::Role::User, "user"},
    };
    if (!rolesToString.contains(role))
        return QString{};
    return rolesToString[role];
}

ChatUser::Role ChatUser::stringToRole(const QString &str)
{
    static const QMap<QString, Role> stringsToRole {
        {"owner", ChatUser::Role::Owner},
        {"admin", ChatUser::Role::Admin},
        {"user", ChatUser::Role::User},
    };
    if (!stringsToRole.contains(str))
        return ChatUser::Role::Unknown;
    return stringsToRole[str];
}

ChatUser ChatUser::fromSqlRecord(const QSqlRecord &record)
{
    ChatUser chatUser;

    chatUser.setChatId(record.value("chat_id").toInt());
    chatUser.setUserId(record.value("user_id").toInt());
    chatUser.setRole(ChatUser::stringToRole(record.value("role").toString()));
    chatUser.setJoinedAt(record.value("joined_at").toDateTime());
    chatUser.setLeftAt(record.value("left_at").toDateTime());

    return chatUser;
}

QDataStream &operator<<(QDataStream &out, const ChatUser &chatUser)
{
    out << chatUser.chatId_   << chatUser.userId_ << chatUser.role_
        << chatUser.joinedAt_ << chatUser.leftAt_;
    return out;
}

QDataStream &operator>>(QDataStream &in, ChatUser &chatUser)
{
    in >> chatUser.chatId_   >> chatUser.userId_ >> chatUser.role_
       >> chatUser.joinedAt_ >> chatUser.leftAt_;
    return in;
}
