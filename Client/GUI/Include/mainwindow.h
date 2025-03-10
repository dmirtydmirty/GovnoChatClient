#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "chatwidget.h"
#include "loadingwidget.h"
#include "packet.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startChating(quint32 id);
    void onMessageFromServer(QSharedPointer<Packet> packet);


private:
    ChatWidget* m_chatWidget;
    LoadingWidget* m_loadingWidget;
    QStackedWidget* m_stackedWidget;

signals:
    void newMessageFromGUI(QSharedPointer<Packet> packet);

private slots:
    void onMessageFromGUI(QString msg);


};
#endif // MAINWINDOW_H
