#include <QLabel>
#include <QGridLayout>

#include "loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent)
    : QWidget{parent}
{
    QLabel* label = new QLabel();
    label->setText("Connecting to server");
    label->setAlignment(Qt::AlignCenter);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(label,0,0);
}
