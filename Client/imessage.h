#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QObject>
#include <QJsonObject>
#include <QMetaProperty>

#include <QDebug>

class IMessage : public QObject
{
    Q_OBJECT
public:

    explicit IMessage() : QObject() {}
    virtual ~IMessage() = default;

    virtual QVariant get() const = 0;

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject& json);
};

#endif // IMESSAGE_H

