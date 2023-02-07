#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <QDataStream>

class DataStream : public QDataStream
{
public:
    DataStream();
    explicit DataStream(QIODevice *d);
    DataStream(QByteArray *d, QIODevice::OpenMode flags);
    DataStream(const QByteArray &d);
};

#endif // DATASTREAM_H
