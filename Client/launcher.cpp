#include "launcher.h"

Launcher::Launcher(QObject *parent)
    : QObject{parent}
{

}

void Launcher::start(){
    client.connectToHost("localhost", 15001);
    connect(&client, &TCPClient::packetReceived, &gui, &MainWindow::pushMessage);
    gui.show();
}
