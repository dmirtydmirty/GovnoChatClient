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


    if (index.data(ChatModel::IsFromSelfRole).toBool()){

        QRect messageRect = QRect(opt.rect.x() + 100 + 10, opt.rect.y() + 5, opt.rect.width() - 100 - 10 , opt.rect.height() - 5);

        painter->fillRect(messageRect, Qt::lightGray);
        painter->drawText(messageRect, Qt::AlignJustify | Qt::TextWordWrap, message);
    }
    else {
        QRect senderIDRect = QRect(opt.rect.x() + 5, opt.rect.y() +  5 , 100, opt.rect.height() -5 );
        QRect messageRect = QRect(opt.rect.x() + 100 + 10, opt.rect.y() + 5, opt.rect.width() - 100 - 100 - 10 , opt.rect.height() - 5);

        painter->fillRect(senderIDRect, Qt::lightGray);
        painter->drawText(senderIDRect, Qt::AlignCenter, "User" + QString::number(senderID));

        painter->fillRect(messageRect, Qt::lightGray);
        painter->drawText(messageRect, Qt::AlignJustify | Qt::TextWordWrap, message);
    }


}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const  {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    QString message = index.data(ChatModel::MessageRole).toString();
    QFontMetrics fm(opt.font);
    QRect bounding_rect = fm.boundingRect(QRect(0, 0, opt.rect.width(), 0), Qt::AlignJustify | Qt::TextWordWrap, message);
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
