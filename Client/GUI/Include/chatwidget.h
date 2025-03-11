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
#include "chatdelegate.h"

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWidget(quint32 id);
    quint32 id() const {return m_id;}

private:
    ChatModel * m_model;

    QListView   *m_listView;
    ChatDelegate * m_chatDelegate;
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
