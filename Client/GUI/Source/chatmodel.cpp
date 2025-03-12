#include "chatmodel.h"

#include <QSize>
ChatModel::ChatModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ChatModel::rowCount(const QModelIndex &parent) const
{
    return m_messages.count();
}

QVariant ChatModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid() || index.row() >= m_messages.size()) {
        return QVariant();
    }
    if (role == MessageRole) {
        return m_messages[index.row()].message();
    }
    else if (role == SenderIdRole) {
        return m_messages[index.row()].senderId();
    }
    else if (role == IsFromSelfRole) {
        return m_messages[index.row()].isFromSelf();
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return m_messages[index.row()].message();
    }
    else {
        return QVariant();
    }
}

bool ChatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if( role != Qt::EditRole ||
        index.column() != 0 ||
        index.row() >= m_messages.count())
        return false;
    m_messages[ index.row() ] = qvariant_cast<ChatMessage>(value);
    emit dataChanged( index, index, {Qt::EditRole} );
    return true;
}

void ChatModel::addMessage(ChatMessage message)
{
    int row = m_messages.size();
    beginInsertRows(QModelIndex(), row, row);
    m_messages.append(message);
    endInsertRows();
}

