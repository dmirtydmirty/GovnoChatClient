#include "tcpclient.h"
#include <QJsonDocument>
#include <QJsonObject>

TCPClient::TCPClient() {
    socket = new QTcpSocket(this);
}

void TCPClient::connectToHost(const QString &host, quint16 port){
    // Connect to the server
    socket->connectToHost(host, port);

    // Connect the readyRead signal to our slot
    connect(socket, &QTcpSocket::readyRead, this, &TCPClient::onReadyRead);
}

void TCPClient::disconnect(){

}

void TCPClient::onReadyRead() {
    while (socket->canReadLine()) {
        QByteArray packet = socket->readAll();
        emit packetReceived(packet);
    }
}

void TCPClient::sendPacket(QString packet){
    socket->write(packet.toUtf8());
}
