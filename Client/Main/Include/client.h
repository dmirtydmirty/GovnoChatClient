#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QPair>
#include <QTimer>

#include "tcpclient.h"
#include "mainwindow.h"
#include "packet.h"

class Client : public QObject
{
    Q_OBJECT
    TCPClient tcpClient;
    MainWindow gui;
    QTimer* reconnectTimer; // kotik
    quint16 reconnectInterval = 2000; // ms
    QPair<QString, quint16> server;

    void readServerConfig();
    void connectToServer();

    enum ClientState{
        Connecting,
        Connected,
        afk,
    } m_state;
public:
    explicit Client(QObject *parent = nullptr);
    void start();
private slots:
    void onSocketDisconnected();
    void onTimeout();
public slots:
    void handlePacket(QString rawPacket);
    void sendPacket(QSharedPointer<Packet>);

};

#endif // CLIENT_H
