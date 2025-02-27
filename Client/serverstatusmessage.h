#ifndef SERVERSTATUSMESSAGE_H
#define SERVERSTATUSMESSAGE_H

#include <QObject>
#include <QString>

#include "imessage.h"

class ServerStatusMessage : public virtual QObject, public virtual IMessage
{
    Q_PROPERTY(QString statusMessage READ statusMessage WRITE setStatusMessage NOTIFY statusMessageChanged FINAL)
public:
    explicit ServerStatusMessage(QObject *parent = nullptr);

    void setStatusMessage(QString statusMessage);
    QString statusMessage() const;

signals:
private:
    QString mStatusMessage;
};

#endif // SERVERSTATUSMESSAGE_H
