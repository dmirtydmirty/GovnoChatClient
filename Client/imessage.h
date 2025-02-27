#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <QObject>
#include <QJsonObject>
#include <QMetaProperty>

class IMessage : public QObject
{
    Q_OBJECT
public:
    explicit IMessage(QObject *parent = nullptr);
    virtual QVariant get() const = 0;

    QJsonObject toJson() const {
        QJsonObject json;
        const QMetaObject* metaObject = this->metaObject();
        for (int i = 0; i < metaObject->propertyCount(); ++i) {
            QMetaProperty metaProperty = metaObject->property(i);
            const char *propertyName = metaProperty.name();
            QVariant propertyValue = this->property(propertyName);

            json[propertyName] = propertyValue.toJsonValue();
        }
        return json;
    }

    void fromJson(const QJsonObject& json) {
        const QMetaObject* metaObject = this->metaObject();
        for (int i = 0; i < metaObject->propertyCount(); ++i) {
            QMetaProperty metaProperty = metaObject->property(i);
            const char *propertyName = metaProperty.name();

            QVariant jsonValue = json.value(propertyName).toVariant();
            setProperty(propertyName, jsonValue);

        }
    }
signals:
};

#endif // IMESSAGE_H

