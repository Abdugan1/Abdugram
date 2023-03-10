#ifndef ABDUMESSAGE_H
#define ABDUMESSAGE_H

#include "../NetCommon_global.h"

#include <QString>
#include "../datastream.h"
#include <QSharedDataPointer>

class AbduMessage;
using AbduMessagePtr = QSharedDataPointer<AbduMessage>;
template<typename T>
using AnyMessagePtr = QSharedDataPointer<T>;

class NETCOMMON_EXPORT AbduMessage : public QSharedData
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
    void fromData(const QByteArray &data);

    //! Constructs QByteArray from class
    //! Base class implementation writes type to it
    virtual QByteArray toData() const;

    //! Returns occupied bytes count for header
    int headerSize() const;

private:
    virtual void gainDataFromPayload(DataStream *stream);

private:
    Type type_;
};

Q_DECLARE_METATYPE(AbduMessagePtr)

#endif // ABDUMESSAGE_H
