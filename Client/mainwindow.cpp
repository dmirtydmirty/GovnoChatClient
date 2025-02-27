#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel();
    model->setColumnCount(0);
    ui->listView->setModel(model);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onSend);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMessageItem(QString msg){
    model->setItem(model->rowCount(), 0, new QStandardItem(msg));
}

void MainWindow::onSend(){
    QString msg = ui->lineEdit->text();
    if (msg.isEmpty())
        return;
    ui->lineEdit->clear();
    addMessageItem("You -> " + msg);

}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Return)
        onSend();
}
