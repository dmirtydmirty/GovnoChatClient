#ifndef SERVERSTATUSMESSAGE_H
#define SERVERSTATUSMESSAGE_H

#include "imessage.h"
#include <QString>

class ServerStatusMessage : public IMessage {
    Q_OBJECT
public:
    explicit ServerStatusMessage() : IMessage() {}
    ~ServerStatusMessage() override = default;

    QString statusInfo() const { return m_statusInfo; }


    void setStatusInfo(const QString &statusInfo) {
        m_statusInfo = statusInfo;
    }

    QVariant get() const override {return statusInfo();}

private:
    Q_PROPERTY(QString StatusInfo READ statusInfo WRITE setStatusInfo)

    QString m_statusInfo;
};

#endif // SERVERSTATUSMESSAGE_H
