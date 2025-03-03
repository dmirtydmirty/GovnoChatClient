#include "client.h"

Client::Client(QObject *parent)
    : QObject{parent}
{}

void Client::start(){
    tcpClient.connectToHost("localhost", 15001);
    connect(&tcpClient, &TCPClient::packetReceived, this, &Client::handlePacket);
    connect(&gui, &MainWindow::newMessageFromGUI, this, &Client::sendPacket);
    gui.show();
}

void Client::handlePacket(QString rawPacket)
{
    QSharedPointer<Packet> packet(new Packet(rawPacket));

    if (packet->get_type() == MessageType::USER_MESSAGE)
        gui.onMessageFromServer(packet);

    if (packet->get_type() == MessageType::USER_ID_NOTIFICATION)
        gui.startChating(packet->get_message()->get().toInt());

}

void Client::sendPacket(QSharedPointer<Packet> packet)
{
    tcpClient.sendPacket(packet->pack());
}
