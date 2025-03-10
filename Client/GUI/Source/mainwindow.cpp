#include "mainwindow.h"
#include "usermessage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(QSize(500, 600));
    m_stackedWidget = new QStackedWidget();
    m_loadingWidget = new LoadingWidget();
    m_stackedWidget->addWidget(m_loadingWidget);

    setCentralWidget(m_stackedWidget);

    m_stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    // kenguru
}

void MainWindow::onMessageFromGUI(QString msg)
{
    QSharedPointer<UserMessage> userMsg(new UserMessage);
    userMsg->setContent(msg);
    QSharedPointer<Packet> packet(new Packet(userMsg, MessageType::USER_MESSAGE, m_chatWidget->id()));
    emit newMessageFromGUI(packet);
}

void MainWindow::startChating(quint32 id)
{
    m_chatWidget = new ChatWidget(id);
    m_stackedWidget->addWidget(m_chatWidget);
    m_stackedWidget->addWidget(m_chatWidget);
    m_stackedWidget->setCurrentIndex(m_stackedWidget->count() - 1);
    connect(m_chatWidget, &ChatWidget::newMessage, this, &MainWindow::onMessageFromGUI);
}

void MainWindow::onMessageFromServer(QSharedPointer<Packet> packet)
{
    QString msg;
    if (packet->get_sender() != 0)
       msg = "User" + QString::number(packet->get_sender()) + " -> " + packet->get_message()->get().toString();
    else
        msg = packet->get_message()->get().toString();
    if (m_chatWidget != nullptr)
        m_chatWidget->addNewMessage(ChatMessage(packet->get_message()->get().toString(), packet->get_sender()));
}


