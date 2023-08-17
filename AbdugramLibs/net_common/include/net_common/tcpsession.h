#ifndef TCPSESSION_H
#define TCPSESSION_H

#include <QTcpSocket>

#include "NetCommon_global.h"
#include "messages/messagesforwarddeclaration.h"

#include "messages/abdumessage.h"

class NETCOMMON_EXPORT TcpSession : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSession(QObject *parent = nullptr);

signals:
    void received(const AbduMessagePtr &message);
    void requestSend(const AbduMessagePtr &message);

public slots:
    bool openSession(quintptr descriptor);
    void closeSession();
    void send(const AbduMessagePtr &message);

private slots:
    void readAvailData();

private:
    void init();
};

#endif // TCPSESSION_H
