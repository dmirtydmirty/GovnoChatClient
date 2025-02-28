#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#include "imessage.h"
#include <QString>

class UserMessage : public IMessage {
    Q_OBJECT
public:
    explicit UserMessage(QObject *parent = nullptr) : IMessage(parent) {}
    ~UserMessage() override = default;

    QString content() const { return m_content; }


    void setContent(const QString &content) {
        m_content = content;
    }

    QVariant get() const override {return content();}

private:
    Q_PROPERTY(QString Content READ content WRITE setContent)

    QString m_content;
};

#endif // USERMESSAGE_H
