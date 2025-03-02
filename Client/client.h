#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QString>

#include "tcpclient.h"
#include "mainwindow.h"
#include "packet.h"

class Client : public QObject
{
    Q_OBJECT
    TCPClient tcpClient;
    MainWindow gui;
public:
    explicit Client(QObject *parent = nullptr);
    void start();
public slots:
    void handlePacket(QString rawPacket);

signals:
    void newUserMessage(QSharedPointer<Packet> userMessagePacket);
};

#endif // CLIENT_H
