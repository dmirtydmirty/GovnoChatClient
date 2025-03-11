#ifndef CHATDELEGATE_H
#define CHATDELEGATE_H


#include <QStyledItemDelegate>

class ChatDelegate : public QStyledItemDelegate {
public:
    explicit ChatDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};
#endif // CHATDELEGATE_H
