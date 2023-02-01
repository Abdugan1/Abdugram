#ifndef TCPSESSION_H
#define TCPSESSION_H

#include <QTcpSocket>

class TcpSession : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSession(QObject *parent = nullptr);

public slots:
    bool open(quintptr descriptor);
};

#endif // TCPSESSION_H
