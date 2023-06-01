#include "data_structures/chat.h"

#include <QSqlRecord>
#include <QVariant>
#include <QDataStream>
#include <QMap>

static const QMap<QString, Chat::Type> StringToType {
    {"private", Chat::Type::Private},
    {"group",   Chat::Type::Group},
    {"channal", Chat::Type::Channel},
};

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

QDataStream &operator<<(QDataStream &out, const Chat &chat)
{
    out << chat.id()        << chat.name()            << chat.description()
        << chat.type()      << chat.createdByUserId() << chat.createdAt()
        << chat.updatedAt() << chat.deletedAt();
    return out;
}

QDataStream &operator>>(QDataStream &in, Chat &chat)
{
    int id = -1;
    QString name;
    QString description;
    Chat::Type type = Chat::Type::Private;
    int createdByUserId = -1;
    QDateTime createdAt;
    QDateTime updatedAt;
    QDateTime deletedAt;

    in >> id        >> name        >> description >> type >> createdByUserId
       >> createdAt >> updatedAt   >> deletedAt;

    chat.setId(id);
    chat.setName(name);
    chat.setDescription(description);
    chat.setType(type);
    chat.setCreatedByUserId(createdByUserId);
    chat.setCreatedAt(createdAt);
    chat.setUpdatedAt(updatedAt);
    chat.setDeletedAt(deletedAt);

    return in;
}

Chat getChatFromQueryResult(const QSqlRecord &record)
{
    Chat chat;

    chat.setId(record.value("id").toInt());
    chat.setName(record.value("name").toString());
    chat.setDescription(record.value("description").toString());
    chat.setType(StringToType[record.value("type").toString()]);
    chat.setCreatedByUserId(record.value("created_by_user_id").toInt());
    chat.setCreatedAt(record.value("created_at").toDateTime());
    chat.setUpdatedAt(record.value("updated_at").toDateTime());
    chat.setDeletedAt(record.value("deleted_at").toDateTime());

    return chat;
}
