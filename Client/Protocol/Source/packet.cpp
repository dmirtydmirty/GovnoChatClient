#include <QJsonDocument>
#include <QJsonObject>

#include "packet.h"
#include "serverstatusmessage.h"
#include "useridnotification.h"
#include "usermessage.h"

Packet::Packet(const QString &raw_packet)
{
    QJsonDocument packet = QJsonDocument::fromJson(raw_packet.toUtf8());
    if (packet.isNull())
        throw std::runtime_error("Incorrect packet format");

    QJsonObject packetJson = packet.object();

    if(!packetJson["Sender"].isDouble())
        throw std::runtime_error("Incorrect packet format");
    if(!packetJson["Type"].isDouble())
        throw std::runtime_error("Incorrect packet format");
    if(!packetJson["Message"].isObject())
        throw std::runtime_error("Incorrect packet format");

    m_sender = packetJson["Sender"].toInt();
    m_type = static_cast<MessageType>(packetJson["Type"].toInt());

    switch (this->m_type)
    {
    case MessageType::USER_MESSAGE :
        m_message = QSharedPointer<UserMessage>(new UserMessage());
        break;
    case MessageType::USER_ID_NOTIFICATION :
        m_message = QSharedPointer<UserIDNotification>(new UserIDNotification());
        break;
    case MessageType::SERVER_STATUS_MESSAGE :
        m_message = QSharedPointer<ServerStatusMessage>(new ServerStatusMessage());
        break;
    default:
        throw std::runtime_error("Unknown message type");
        break;
    }
    m_message->fromJson(packetJson["Message"].toObject());

}

Packet::Packet(const QSharedPointer<IMessage> &msg, MessageType type, quint32 sender):
    m_sender(sender),
    m_type(type),
    m_message(msg)
{}

QString Packet::pack() const
{
    QJsonObject packetJson;
    packetJson["Type"] = static_cast<quint8>(this->m_type);
    packetJson["Sender"] =  static_cast<qint64>(m_sender);
    packetJson["Message"] = m_message->toJson();

    QJsonDocument packet(packetJson);

    return QString::fromUtf8(packet.toJson());
}
