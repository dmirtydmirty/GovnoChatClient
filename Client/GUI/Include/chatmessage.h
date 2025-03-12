#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QString>
#include <QtTypes>
#include <QMetaType>

class ChatMessage{
    QString m_message;
    quint32 m_senderId;
    bool m_fromSelf;
public:
    ChatMessage(QString message = "", quint32 senderId = 0, bool fromSelf = false):
        m_message(message), m_senderId(senderId), m_fromSelf(fromSelf)
    {}
    ChatMessage(const ChatMessage& other):
        m_message(other.m_message), m_senderId(other.m_senderId)
    {}

    QString message() const {return m_message;}
    quint32 senderId() const {return m_senderId;}
    bool isFromSelf() const {return m_fromSelf;}
    bool operator=(const ChatMessage& other){ return other.m_message == m_message && other.m_senderId == m_senderId;}
};


Q_DECLARE_METATYPE(ChatMessage);

#endif // CHATMESSAGE_H
