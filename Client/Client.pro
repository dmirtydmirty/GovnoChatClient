QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/Source/chatwidget.cpp \
    GUI/Source/loadingwidget.cpp \
    GUI/Source/mainwindow.cpp \
    GUI/Source/settingswidget.cpp \
    Main/Source/client.cpp \
    Main/Source/main.cpp \
    Protocol/Source/imessage.cpp \
    Protocol/Source/packet.cpp \
    Tcp/Source/tcpclient.cpp \


INCLUDEPATH += \
    GUI/Include/        \
    Main/Include/       \
    Protocol/Include/   \
    Tcp/Include/

HEADERS += \
    GUI/Include/chatwidget.h \
    GUI/Include/loadingwidget.h \
    GUI/Include/mainwindow.h \
    GUI/Include/settingswidget.h \
    Main/Include/client.h \
    Protocol/Include/imessage.h \
    Protocol/Include/packet.h \
    Protocol/Include/protocol.h \
    Protocol/Include/serverstatusmessage.h \
    Protocol/Include/useridnotification.h \
    Protocol/Include/usermessage.h \
    Tcp/Include/tcpclient.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
