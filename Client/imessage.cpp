#include "imessage.h"

QJsonObject IMessage::toJson() const {
    QJsonObject json;
    const QMetaObject* metaObject = this->metaObject();

    for (int i = 0; i < metaObject->propertyCount(); ++i) {
        QMetaProperty metaProperty = metaObject->property(i);
        const char *propertyName = metaProperty.name();

        if (strcmp(propertyName, "objectName") == 0)
            continue;

        QVariant propertyValue = this->property(propertyName);

        json[propertyName] = propertyValue.toJsonValue();
    }
    return json;
}

void IMessage::fromJson(const QJsonObject& json) {
    const QMetaObject* metaObject = this->metaObject();
    for (int i = 0; i < metaObject->propertyCount(); ++i) {
        QMetaProperty metaProperty = metaObject->property(i);
        const char *propertyName = metaProperty.name();

        if (json.contains(propertyName)) {
            QJsonValue jsonValue = json.value(propertyName);
            QVariant variantValue = jsonValue.toVariant();

            setProperty(propertyName, variantValue);

        }

    }
}
