#ifndef ABDUMESSAGE_H
#define ABDUMESSAGE_H

#include <QString>
#include "../datastream.h"
#include <QSharedDataPointer>

class AbduMessage;
using AbduMessagePtr = QSharedDataPointer<AbduMessage>;

class AbduMessage : public QSharedData
{
public:
    // !!!Add new types to end for version independent!!!
    enum class Type : int {
        Unknown = -1,

        ClientSide = 0,
        Login      = ClientSide + 1,
        Register,

        ServerSide = 1000000,
        LoginStatus = ServerSide + 1,
        RegisterStaus,
    };

public:
    explicit AbduMessage(Type type);
    virtual ~AbduMessage();

    Type type() const;

    //! Sets data info to class
    //! Base class implementation just skips type
    virtual void fromData(const QByteArray &data);

    //! Constructs QByteArray from class
    //! Base class implementation writes type to it
    virtual QByteArray toData() const;

private:
    Type type_;
};

#endif // ABDUMESSAGE_H
