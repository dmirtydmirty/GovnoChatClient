#include "chatmodel.h"


ChatModel::ChatModel(QObject *parent)
{

}

int ChatModel::rowCount(const QModelIndex &parent) const
{
    return m_messages.count();
}

QVariant ChatModel::data(const QModelIndex &index, int role) const
{
    int idx = index.row();
    switch (role) {
    case Qt::DisplayRole:
        if (m_messages[idx].senderId() != 0)
            return QString("User" + QString::number(m_messages[idx].senderId()) + " -> " + m_messages[idx].message());
        else
            return QString(m_messages[idx].message());
    case ChatRoles::MessageRole:
        return m_messages[idx].message();
    case ChatRoles::SenderIdRole:
        return m_messages[idx].senderId();
    default:
        return QString("Frog object");
        break;
    }
}

void ChatModel::addMessage(const ChatMessage &message)
{
    m_messages.append(message);
}
