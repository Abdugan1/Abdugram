#include "data_structures/chat.h"

#include <QSqlRecord>
#include <QVariant>
#include <QDataStream>
#include <QMap>

Chat::Chat()
{

}

int Chat::id() const
{
    return id_;
}

void Chat::setId(int newId)
{
    id_ = newId;
}

QString Chat::name() const
{
    return name_;
}

void Chat::setName(const QString &newName)
{
    name_ = newName;
}

int Chat::createdByUserId() const
{
    return createdByUserId_;
}

void Chat::setCreatedByUserId(int newCreatedByUserId)
{
    createdByUserId_ = newCreatedByUserId;
}

Chat::Type Chat::type() const
{
    return type_;
}

void Chat::setType(Type newType)
{
    type_ = newType;
}

QString Chat::description() const
{
    return description_;
}

void Chat::setDescription(const QString &newDescription)
{
    description_ = newDescription;
}

QDateTime Chat::createdAt() const
{
    return createdAt_;
}

void Chat::setCreatedAt(const QDateTime &newCreatedAt)
{
    createdAt_ = newCreatedAt;
}

QDateTime Chat::updatedAt() const
{
    return updatedAt_;
}

void Chat::setUpdatedAt(const QDateTime &newUpdatedAt)
{
    updatedAt_ = newUpdatedAt;
}

QDateTime Chat::deletedAt() const
{
    return deletedAt_;
}

void Chat::setDeletedAt(const QDateTime &newDeletedAt)
{
    deletedAt_ = newDeletedAt;
}

QString Chat::typeToString(Type type)
{
    static const QMap<Type, QString> types {
        {Chat::Type::Private, "private"},
        {Chat::Type::Group, "group"},
        {Chat::Type::Channel, "channel"},
    };
    if (!types.contains(type))
        return QString{};
    return types[type];
}

Chat::Type Chat::stringToType(const QString &str)
{
    static const QMap<QString, Chat::Type> types{
        {"private", Chat::Type::Private},
        {"group",   Chat::Type::Group},
        {"channal", Chat::Type::Channel},
    };
    if (!types.contains(str))
        return Type::Unknown;
    return types[str];
}

Chat Chat::fromSqlRecord(const QSqlRecord &record)
{
    Chat chat;

    chat.setId(record.value("id").toInt());
    chat.setName(record.value("name").toString());
    chat.setDescription(record.value("description").toString());
    chat.setType(Chat::stringToType(record.value("type").toString()));
    chat.setCreatedByUserId(record.value("created_by_user_id").toInt());
    chat.setCreatedAt(record.value("created_at").toDateTime());
    chat.setUpdatedAt(record.value("updated_at").toDateTime());
    chat.setDeletedAt(record.value("deleted_at").toDateTime());

    return chat;
}

QDataStream &operator<<(QDataStream &out, const Chat &chat)
{
    out << chat.id_        << chat.name_            << chat.description_
        << chat.type_      << chat.createdByUserId_ << chat.createdAt_
        << chat.updatedAt_ << chat.deletedAt_;
    return out;
}

QDataStream &operator>>(QDataStream &in, Chat &chat)
{
    in >> chat.id_        >> chat.name_            >> chat.description_
       >> chat.type_      >> chat.createdByUserId_ >> chat.createdAt_
       >> chat.updatedAt_ >> chat.deletedAt_;

    return in;
}
