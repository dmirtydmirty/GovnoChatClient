#include "chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent)
    : QWidget{parent}
{
    m_verticalLayout = new QVBoxLayout(this);
    m_horizontalLayout = new QHBoxLayout();
    m_lineEdit = new QLineEdit();
    m_pushButton = new QPushButton("Send");
    m_listView = new QListView();
    m_listView->setMinimumSize(QSize(500, 600));

    m_verticalLayout->addWidget(m_listView);

    m_horizontalLayout->addWidget(m_lineEdit);
    m_horizontalLayout->addWidget(m_pushButton);
    m_verticalLayout->addLayout(m_horizontalLayout);
}
