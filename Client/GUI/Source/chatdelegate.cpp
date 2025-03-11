#include <QPainter>

#include "chatdelegate.h"
#include "chatmodel.h"

ChatDelegate::ChatDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) {
        return;
    }

    QString message = index.data(ChatModel::MessageRole).toString();
    int senderId = index.data(ChatModel::SenderIdRole).toInt();

    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    painter->save();
    if (opt.state & QStyle::State_Selected) {
        painter->fillRect(opt.rect, opt.palette.highlight());
    } else {
        painter->fillRect(opt.rect, opt.palette.base());
    }

    int padding = 5;
    int senderIdX = opt.rect.left() + padding;
    int senderIdY = opt.rect.top() + 15;
    int messageX = senderIdX + 100;
    int messageY = senderIdY;

    QString senderIdText = QString("user%1:").arg(senderId);
    painter->setPen(opt.palette.color(QPalette::Text));
    painter->drawText(senderIdX, senderIdY, senderIdText);

    painter->drawText(messageX, messageY, message);

    painter->restore();
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const  {
    QFontMetrics fm(option.font);
    QString message = index.data(ChatModel::MessageRole).toString();
    QString senderIdText = QString("Sender ID: %1").arg(index.data(ChatModel::SenderIdRole).toInt());

    int lineHeight = fm.height();
    int height = lineHeight * 2 + 5;
    int width = option.rect.width();
    return QSize(width, height);
}
