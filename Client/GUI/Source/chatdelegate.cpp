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
    bool isFromSelf = index.data(ChatModel::IsFromSelfRole).toBool();

    QFontMetrics fm(opt.font);
    QRect bounding_rect = fm.boundingRect(QRect(0, 0, m_messageFieldMaxWidth - 2 * m_textPadding, 0), Qt::AlignJustify | Qt::TextWordWrap, message);

    if (isFromSelf){

        QRect messageRect(opt.rect.x() + opt.rect.width() - bounding_rect.width() - m_padding - 2 * m_textPadding,
                        opt.rect.y() + m_padding,
                        bounding_rect.width() + 2 * m_textPadding,
                        opt.rect.height() -  m_padding );

        QRect textRect(messageRect.x() + m_textPadding,
                        messageRect.y() + m_textPadding,
                        messageRect.width() - 2 * m_textPadding,
                        messageRect.height() - 2 * m_textPadding);

        painter->setBrush(QBrush(Qt::lightGray));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(messageRect, m_cornerRadius, m_cornerRadius);
        painter->setPen(Qt::black);
        painter->drawText(textRect, Qt::AlignJustify | Qt::TextWordWrap | Qt::AlignVCenter, message);
    }
    else {
        QRect senderIDRect = QRect(opt.rect.x() + m_padding ,
                                   opt.rect.y() +  m_padding,
                                   m_senderFieldWidth,
                                   opt.rect.height() -  m_padding );
        QRect messageRect = QRect(opt.rect.x() + m_senderFieldWidth + 2 * m_padding,
                                  opt.rect.y() + m_padding,
                                  bounding_rect.width()  + 2 * m_textPadding,
                                  opt.rect.height() - m_padding);

        QRect textRect(messageRect.x() + m_textPadding,
                       messageRect.y() + m_textPadding,
                       messageRect.width() - 2 * m_textPadding,
                       messageRect.height() - 2 * m_textPadding);


        painter->setBrush(QBrush(Qt::lightGray));
        painter->setPen(Qt::NoPen);

        painter->drawRoundedRect(senderIDRect, m_cornerRadius, m_cornerRadius);
        painter->drawRoundedRect(messageRect, m_cornerRadius, m_cornerRadius);

        painter->setPen(Qt::black);

        if (senderID != 0)
            painter->drawText(senderIDRect, Qt::AlignCenter, "User" + QString::number(senderID));
        else
            painter->drawText(senderIDRect, Qt::AlignCenter, "Server");

        painter->drawText(textRect, Qt::AlignJustify | Qt::TextWordWrap | Qt::AlignVCenter, message);
    }


}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const  {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    QString message = index.data(ChatModel::MessageRole).toString();
    QFontMetrics fm(opt.font);
    QRect bounding_rect = fm.boundingRect(QRect(0, 0, m_messageFieldMaxWidth - 2 * m_textPadding, 0), Qt::AlignJustify | Qt::TextWordWrap, message);
    return QSize(m_messageFieldMaxWidth + 3 * m_padding + m_senderFieldWidth + 2 * m_textPadding,
                 bounding_rect.height() + 2 * m_padding + 2 * m_textPadding);
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
