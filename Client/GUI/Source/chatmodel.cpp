#include "chatmodel.h"

#include <QSize>
ChatModel::ChatModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_messages << ChatMessage("1", 1);
    m_messages << ChatMessage("2", 2);
    m_messages << ChatMessage("3", 3);
    m_messages << ChatMessage("4", 4);
    m_messages << ChatMessage("5", 5);
}

int ChatModel::rowCount(const QModelIndex &parent) const
{
    return m_messages.count();
}

QVariant ChatModel::data(const QModelIndex &index, int role) const
{

    qDebug() << QString("row %1, col%2, role %3").arg(index.row()).arg(index.column()).arg(role);
    if( role != Qt::DisplayRole || role != Qt::EditRole )
        return QVariant();
    if( index.column() == 0 && index.row() < m_messages.count() )
        return" m_messages.at( index.row() ).senderId()";
    else
        return QVariant();
}

bool ChatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << QString("row %1, col%2, role %3").arg(index.row()).arg(index.column()).arg(role);
    if( role != Qt::EditRole ||
        index.column() != 0 ||
        index.row() >= m_messages.count() +1 )
        return false;
    else if (index.row() == m_messages.count() +1 ) {
        m_messages.append(qvariant_cast<ChatMessage>(value));
        return true;
    }
    m_messages[ index.row() ] = qvariant_cast<ChatMessage>(value);
    // emit dataChanged( index, index );
    return true;
}


// Qt::ItemFlags ChatModel::flags(const QModelIndex &index) const
// {
//     if(!index.isValid())
//         return Qt::ItemIsEnabled;
//     return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
// }
