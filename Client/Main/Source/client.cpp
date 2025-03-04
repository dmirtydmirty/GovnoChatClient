#include "client.h"
#include <QFile>

Client::Client(QObject *parent)
    : QObject{parent}
{}

void Client::start(){
    tcpClient.connectToHost("127.0.0.1", 15001);
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
