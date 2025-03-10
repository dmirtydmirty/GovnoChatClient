#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QtTypes>

#include "imessage.h"

enum MessageType : quint8 {
    USER_MESSAGE=0,

    USER_ID_NOTIFICATION=1,
    SERVER_STATUS_MESSAGE=2,
};

class Packet : public QObject
{
    Q_OBJECT
public:
    Packet(const QString& raw_packet);
    Packet(const QSharedPointer<IMessage>& msg, MessageType type, quint32 sender);

    MessageType get_type() const {return m_type;}
    uint32_t get_sender() const {return m_sender;}
    QSharedPointer<IMessage> get_message() const {return m_message;}
    QString pack() const;

private:

    quint32 m_sender;
    MessageType m_type;
    QSharedPointer<IMessage> m_message;

};

#endif // PACKET_H
