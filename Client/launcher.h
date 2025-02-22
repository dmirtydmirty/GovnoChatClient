#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>

#include "tcpclient.h"
#include "mainwindow.h"
class Launcher : public QObject
{
    Q_OBJECT
    TCPClient client;
    MainWindow gui;
public:
    explicit Launcher(QObject *parent = nullptr);
    void start();

signals:
};

#endif // LAUNCHER_H
