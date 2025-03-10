#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QString>
#include <QtTypes>

class ChatMessage{
    QString m_message;
    quint32 m_senderId;
public:
    ChatMessage(QString message, quint32 senderId):
        m_message(message), m_senderId(senderId)
    {}

    QString message() const {return m_message;}
    quint32 senderId() const {return m_senderId;}
};


#endif // CHATMESSAGE_H
