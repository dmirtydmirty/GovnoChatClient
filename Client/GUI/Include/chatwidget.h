#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QString>
#include <QStandardItemModel>
#include <QKeyEvent>

#include "chatmodel.h"

class ChatWidget : public QWidget
{
    Q_OBJECT
    ChatModel * m_model;
public:
    explicit ChatWidget(quint32 id);
    quint32 id() const {return m_id;}

private:
    QListView   *m_listView;
    QLineEdit   *m_lineEdit;
    QPushButton *m_pushButton;

    QVBoxLayout *m_verticalLayout;
    QHBoxLayout *m_horizontalLayout;
    QGroupBox   *m_groupeBox;
    quint32     m_id;

public:
    void keyPressEvent(QKeyEvent* event);
    void addNewMessage(ChatMessage msg);

private slots:
    void onSend();

signals:
    void newMessage(QString msg);



};

#endif // CHATWIDGET_H
