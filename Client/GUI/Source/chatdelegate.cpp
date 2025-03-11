#include <QPainter>
#include <QStyleOptionViewItem>
#include <QString>
#include <QMouseEvent>
#include <QWidget>

#include "chatdelegate.h"
#include "chatmodel.h"

ChatDelegate::ChatDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    quint32 senderID = index.data(ChatModel::SenderIdRole).toInt();
    QString message = index.data(ChatModel::MessageRole).toString();

    QRect senderIDRect = QRect(opt.rect.x(), opt.rect.y(), 100, opt.rect.height());
    QRect messageRect = QRect(opt.rect.x() + 100, opt.rect.y(), opt.rect.width() - 100, opt.rect.height());

    const_cast<QAbstractItemModel*>(index.model())->setData(index, QVariant::fromValue(senderIDRect), Qt::UserRole + 2);
    const_cast<QAbstractItemModel*>(index.model())->setData(index, QVariant::fromValue(messageRect), Qt::UserRole + 3);

    painter->fillRect(senderIDRect, Qt::lightGray);
    painter->drawText(senderIDRect, Qt::AlignCenter, "User" + QString::number(senderID));

    painter->fillRect(messageRect, Qt::white);
    painter->drawText(messageRect, Qt::AlignCenter | Qt::TextWordWrap, message);

    if (option.state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::black, 20));
        painter->drawRect(opt.rect.adjusted(0, 0, 0, 0));
    }
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const  {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    QString message = index.data(ChatModel::MessageRole).toString();
    QFontMetrics fm(opt.font);
    QRect bounding_rect = fm.boundingRect(QRect(0, 0, 200, 0), Qt::AlignLeft | Qt::TextWordWrap, message);
    return QSize(bounding_rect.width(), bounding_rect.height() + 20);
}


bool ChatDelegate:: editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)  {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        QRect authorRect = index.data(Qt::UserRole + 2).toRect();
        QRect messageRect = index.data(Qt::UserRole + 3).toRect();

        QPoint viewportPos = static_cast<QWidget*>(parent())->mapToGlobal(QPoint(0, 0));

        authorRect.translate(-viewportPos.x(), -viewportPos.y());
        messageRect.translate(-viewportPos.x(), -viewportPos.y());


        QPoint itemViewPos = static_cast<QWidget*>(parent())->mapToGlobal(QPoint(0, 0));
        authorRect.translate(itemViewPos.x(), itemViewPos.y());
        messageRect.translate(itemViewPos.x(), itemViewPos.y());

        int authorId = index.data(ChatModel::SenderIdRole).toInt();

        if (authorRect.contains(mouseEvent->pos())) {
            qDebug() << "Clicked on author: " << index.data(ChatModel::SenderIdRole).toString() << " with ID: " << authorId;
            // emit authorClicked(authorId); // Emit the authorClicked signal
            return true; // Consume event
        } else if (messageRect.contains(mouseEvent->pos())) {
            qDebug() << "Clicked on message: " << index.data(ChatModel::MessageRole).toString();
            // emit messageClicked(index); // Emit the messageClicked signal with the index
            return true; // Consume event
        }

        return false;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
