#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QStackedWidget>

#include "chatwidget.h"
#include "loadingwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStandardItemModel * m_model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event);

private:
    ChatWidget* m_chatWidget;
    LoadingWidget* m_loadingWidget;
    QStackedWidget* m_stackedWidget;

signals:
    void newMessage(QString msg);

private slots:
    void onSend();

public slots:
    void addMessageItem(QString msg);
    void setChatInterface(quint32 id);
    void setLoadingScreen();


};
#endif // MAINWINDOW_H
