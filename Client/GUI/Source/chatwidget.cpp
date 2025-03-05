#include "chatwidget.h"

ChatWidget::ChatWidget(quint32 id)
    : m_id{id}
{
    m_verticalLayout = new QVBoxLayout(this);
    m_horizontalLayout = new QHBoxLayout();
    m_lineEdit = new QLineEdit();
    m_pushButton = new QPushButton("Send");
    m_listView = new QListView();


    m_verticalLayout->addWidget(m_listView);

    m_horizontalLayout->addWidget(m_lineEdit);
    m_horizontalLayout->addWidget(m_pushButton);
    m_verticalLayout->addLayout(m_horizontalLayout);


    m_model = new QStandardItemModel();
    m_model->setColumnCount(0);
    m_listView->setModel(m_model);

    connect(m_pushButton, &QPushButton::clicked, this, &ChatWidget::onSend);
    addNewMessage("Wellcome to chat, your id is " + QString::number(m_id));
}

void ChatWidget::addNewMessage(QString msg){
    m_model->setItem(m_model->rowCount(), 0, new QStandardItem(msg));
}


void ChatWidget::onSend(){
    QString msg = m_lineEdit->text();
    if (msg.isEmpty())
        return;
    m_lineEdit->clear();
    addNewMessage("You -> " + msg);
    emit newMessage(msg);

}

void ChatWidget::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Return)
        onSend();
}
