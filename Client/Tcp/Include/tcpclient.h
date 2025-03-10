#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TCPClient : public QObject
{
    Q_OBJECT
    QTcpSocket *socket;
public:
    TCPClient();

    void connectToHost(const QString &host, quint16 port);
    void disconnect();

signals:
    void packetReceived(QString packet);

private slots:
    void onReadyRead();

public slots:
    void sendPacket(QString packet);
};

#endif // TCPCLIENT_H
