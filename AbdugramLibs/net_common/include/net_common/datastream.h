#ifndef DATASTREAM_H
#define DATASTREAM_H

#include "NetCommon_global.h"

#include <QDataStream>

class NETCOMMON_EXPORT DataStream : public QDataStream
{
public:
    DataStream();
    explicit DataStream(QIODevice *d);
    DataStream(QByteArray *d, OpenMode flags);
    DataStream(const QByteArray &d);
};

#endif // DATASTREAM_H
