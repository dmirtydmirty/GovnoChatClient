#include "tcpclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>

TCPClient::TCPClient() {
    socket = new QTcpSocket(this);
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    connect(socket, &QTcpSocket::readyRead, this, &TCPClient::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TCPClient::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, [&](QAbstractSocket::SocketError socketError) {
        qDebug() << "Socket error occurred: " << socketError;
    });
}

void TCPClient::connectToHost(const QString &host, quint16 port){
    qDebug() << "Connecting to host: " << host << ":" << port;
    socket->connectToHost(host, port);
}

void TCPClient::disconnect(){
    socket->abort();
    emit disconnected();
}

void TCPClient::onReadyRead() {
    while (socket->canReadLine()) {
        QByteArray packet = socket->readAll();
        emit packetReceived(packet);
    }
}

void TCPClient::onDisconnected(){
    emit disconnected();
}

void TCPClient::sendPacket(QString packet){
    socket->write(packet.toUtf8());
}
