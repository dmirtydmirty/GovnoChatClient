#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_stackedWidget = new QStackedWidget();
    m_loadingWidget = new LoadingWidget();
    m_chatWidget = new ChatWidget();
    m_stackedWidget->addWidget(m_chatWidget);
    m_stackedWidget->addWidget(m_loadingWidget);

    setCentralWidget(m_stackedWidget);
    m_model = new QStandardItemModel();
    m_model->setColumnCount(0);
    m_chatWidget->m_listView->setModel(m_model);

    connect(m_chatWidget->m_pushButton, &QPushButton::clicked, this, &MainWindow::onSend);
    m_stackedWidget->setCurrentIndex(1);
}


MainWindow::~MainWindow()
{
    // delete ui;
}

void MainWindow::addMessageItem(QString msg){
    m_model->setItem(m_model->rowCount(), 0, new QStandardItem(msg));
}

void MainWindow::setChatInterface()
{
    m_stackedWidget->setCurrentIndex(0);
}

void MainWindow::setLoadingScreen(quint32)
{
    m_stackedWidget->setCurrentIndex(1);
}

void MainWindow::onSend(){
    QString msg = m_chatWidget->m_lineEdit->text();
    if (msg.isEmpty())
        return;
    m_chatWidget->m_lineEdit->clear();
    addMessageItem("You -> " + msg);

}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Return)
        onSend();
}
