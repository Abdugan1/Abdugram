#include "tcpsession.h"
#include "datastream.h"
#include "messages/abdumessagefactory.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

TcpSession::TcpSession(QObject *parent)
    : QTcpSocket{parent}
{
    init();
}

bool TcpSession::openSession(quintptr descriptor)
{
    if (!setSocketDescriptor(descriptor)) {
        return false;
    }

    return true;
}

void TcpSession::closeSession()
{
    disconnectFromHost();
}

void TcpSession::send(const AbduMessagePtr &message)
{
    Q_ASSERT(message);
    if (!isValid() && !message)
        return;

    DataStream socketStream{this};
    socketStream << message->toData();
    flush();
}

void TcpSession::readAvailData()
{
    qDebug() << "Data is available";
    DataStream stream{this};
    while (true) {
        stream.startTransaction();
        QByteArray data;
        stream >> data;
        if (!stream.commitTransaction())
            return; // The message may come in chuncks, so wait for more

        qDebug() << "Data transaction was succesfully";

        auto abduMessage = AbduMessageFactory::fromData(data);

        if (!abduMessage) {
            qWarning() << "Unknown abdu message type or invalid data send" << data;
            return;
        }

        emit received(abduMessage);
    }
}

void TcpSession::init()
{
    connect(this, &TcpSession::readyRead, this, &TcpSession::readAvailData);
}
