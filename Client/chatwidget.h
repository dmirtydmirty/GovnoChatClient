#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QString>

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWidget(QWidget *parent = nullptr);

public:
    QListView   *m_listView;
    QLineEdit   *m_lineEdit;
    QPushButton *m_pushButton;
private:
    QVBoxLayout *m_verticalLayout;
    QHBoxLayout *m_horizontalLayout;
    QGroupBox   *m_groupeBox;



};

#endif // CHATWIDGET_H
