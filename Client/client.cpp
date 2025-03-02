#include "client.h"

Client::Client(QObject *parent)
    : QObject{parent}
{}

void Client::start(){
    tcpClient.connectToHost("localhost", 15001);
    connect(&tcpClient, &TCPClient::packetReceived, &gui, &MainWindow::addMessageItem);
    gui.show();
}

void Client::handlePacket(QString rawPacket)
{
    QSharedPointer<Packet> packet(new Packet(rawPacket));

    if (packet->get_type() == MessageType::USER_MESSAGE)
        emit newUserMessage(packet);

}
