#ifndef CHATDELEGATE_H
#define CHATDELEGATE_H


#include <QStyledItemDelegate>

class ChatDelegate : public QStyledItemDelegate {

    quint16 m_messageFieldMaxWidth = 400;
    quint16 m_messageFieldMinWidth = 100;
    quint16 m_senderFieldWidth = 100;

    quint16 m_padding = 5;
    quint8 m_textPadding = 10;
    quint8 m_cornerRadius= 3;
public:
    explicit ChatDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};
#endif // CHATDELEGATE_H
