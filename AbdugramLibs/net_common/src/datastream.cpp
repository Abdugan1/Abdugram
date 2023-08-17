#include "datastream.h"

DataStream::DataStream()
{
    setVersion(Qt_5_15);
}

DataStream::DataStream(QIODevice *d)
    : QDataStream{d}
{
    setVersion(Qt_5_15);
}

DataStream::DataStream(QByteArray *d, OpenMode flags)
    : QDataStream{d, flags}
{
    setVersion(Qt_5_15);
}

DataStream::DataStream(const QByteArray &d)
    : QDataStream{d}
{
    setVersion(Qt_5_15);
}
