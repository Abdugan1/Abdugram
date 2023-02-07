#ifndef TCPSESSION_H
#define TCPSESSION_H

#include <QTcpSocket>

#include "messages/abdumessage.h"

class TcpSession : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSession(QObject *parent = nullptr);

signals:
    void received(const AbduMessagePtr &message);

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
