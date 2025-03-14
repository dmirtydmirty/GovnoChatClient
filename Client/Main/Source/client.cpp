#include "client.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(QObject *parent)
    : QObject{parent}, m_state{ClientState::afk}, reconnectTimer{new QTimer(this)}
{
    connect(&tcpClient, &TCPClient::packetReceived, this, &Client::handlePacket);
    connect(&tcpClient, &TCPClient::disconnected, this, &Client::onSocketDisconnected);
    connect(&gui, &MainWindow::newMessageFromGUI, this, &Client::sendPacket);
    connect(reconnectTimer, &QTimer::timeout, this, &Client::onTimeout);

    reconnectTimer->setInterval(reconnectInterval);
}

void Client::readServerConfig()
{
    QString dafault_path = "srv.json";
    QFile cfg(dafault_path);
    if (cfg.open(QIODevice::ReadOnly)){
        QTextStream in(&cfg);
        QJsonDocument doc = QJsonDocument::fromJson(in.readAll().toUtf8());
        QJsonObject obj = doc.object();
        if (obj["host"].isString() && obj["port"].isDouble())
            server = QPair(obj["host"].toString(), obj["port"].toInt());
        cfg.close();
    }

}

void Client::connectToServer()
{
    readServerConfig();
    tcpClient.connectToHost(server.first, server.second);
}

void Client::start(){
    connectToServer();
    m_state = ClientState::Connecting;
    reconnectTimer->start();
    gui.show();
}

void Client::onSocketDisconnected()
{
    qDebug() << "Socket disconnected";
    connectToServer();
    reconnectTimer->start();
}

void Client::onTimeout()
{
    reconnectTimer->stop();
    qDebug() << "Timeout";
    tcpClient.disconnect();
}

void Client::handlePacket(QString rawPacket)
{
    QSharedPointer<Packet> packet(new Packet(rawPacket));


    switch (packet->get_type()) {
    case MessageType::USER_MESSAGE:
        gui.onMessageFromServer(packet);
        break;
    case MessageType::SERVER_STATUS_MESSAGE:
        gui.onMessageFromServer(packet);
        break;
    case MessageType::USER_ID_NOTIFICATION:
        m_state = ClientState::Connected;
        reconnectTimer->stop();
        gui.startChating(packet->get_message()->get().toInt());
        break;
    default:
        break;
    }

}

void Client::sendPacket(QSharedPointer<Packet> packet)
{
    tcpClient.sendPacket(packet->pack());
}
