#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QList>

#include "chatmessage.h"


class ChatModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum ChatRoles {
        MessageRole = Qt::UserRole + 1,
        SenderIdRole,
    };

    explicit ChatModel(QObject *parent = nullptr);


    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[MessageRole] = "message";
        roles[SenderIdRole] = "senderId";
        return roles;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addMessage(const ChatMessage& message);
private:
    QList<ChatMessage> m_messages;
};
#endif // CHATMODEL_H
