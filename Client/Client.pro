QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/Source/chatwidget.cpp \
    GUI/Source/loadingwidget.cpp \
    GUI/Source/mainwindow.cpp \
    Main/Source/client.cpp \
    Main/Source/main.cpp \
    Protocol/Source/imessage.cpp \
    Protocol/Source/packet.cpp \
    Tcp/Source/tcpclient.cpp

INCLUDEPATH += \
    GUI/Include/        \
    Main/Include/       \
    Protocol/Include/   \
    Tcp/Include/

HEADERS += \
    GUI/Include/chatwidget.h \
    GUI/Include/loadingwidget.h \
    GUI/Include/mainwindow.h \
    Main/Include/client.h \
    Protocol/Include/imessage.h \
    Protocol/Include/packet.h \
    Protocol/Include/protocol.h \
    Protocol/Include/serverstatusmessage.h \
    Protocol/Include/useridnotification.h \
    Protocol/Include/usermessage.h \
    Tcp/Include/tcpclient.h


#  Configuration
CONFIG_DIR = Config
CONFIG_FILE = $$PWD/$${CONFIG_DIR}/srv.json

CONFIG_FILES.sources = $${CONFIG_FILE}
CONFIG_FILES.target = $$DESTDIR/$${CONFIG_DIR}

QMAKE_EXTRA_FILES += $${CONFIG_FILES.sources}

createdir.input = CONFIG_FILES.target
createdir.output = .
createdir.commands = mkdir -p "$$quote($${createdir.input})"
createdir.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += createdir

copyconfig.input = CONFIG_FILES.sources
copyconfig.output = $${CONFIG_FILES.target}
copyconfig.commands = $(COPY_FILE) "$$quote($${copyconfig.input})" "$$quote($${copyconfig.output})"
copyconfig.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += copyconfig

# Print config info
message("DESTDIR: $$DESTDIR")
message("CONFIG_DIR: $$CONFIG_DIR")
message("CONFIG_FILE: $$CONFIG_FILE")
message("CONFIG_FILES.target: $$CONFIG_FILES.target")

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
