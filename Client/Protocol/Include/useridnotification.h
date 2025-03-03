#ifndef USERIDNOTIFICATION_H
#define USERIDNOTIFICATION_H

#include "imessage.h"
#include <QtTypes>

class UserIDNotification : public IMessage {
    Q_OBJECT
public:
    explicit UserIDNotification() : IMessage() {}
    ~UserIDNotification() override = default;

    quint32 id() const { return m_id; }


    void seId(quint32 id) {
        m_id = id;
    }

    QVariant get() const override {return id();}

private:
    Q_PROPERTY(quint32 ID READ id WRITE seId)

    quint32 m_id;
};
#endif // USERIDNOTIFICATION_H
