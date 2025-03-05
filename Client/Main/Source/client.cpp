#include "client.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Client::Client(QObject *parent)
    : QObject{parent}
{}

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
    }

}

void Client::start(){
    readServerConfig();
    tcpClient.connectToHost(server.first, server.second);
    connect(&tcpClient, &TCPClient::packetReceived, this, &Client::handlePacket);
    connect(&gui, &MainWindow::newMessageFromGUI, this, &Client::sendPacket);
    gui.show();
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
