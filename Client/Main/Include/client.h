#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QPair>

#include "tcpclient.h"
#include "mainwindow.h"
#include "packet.h"

class Client : public QObject
{
    Q_OBJECT
    TCPClient tcpClient;
    MainWindow gui;
    QPair<QString, quint16> server;

    void readServerConfig();
public:
    explicit Client(QObject *parent = nullptr);
    void start();
public slots:
    void handlePacket(QString rawPacket);
    void sendPacket(QSharedPointer<Packet>);

};

#endif // CLIENT_H
