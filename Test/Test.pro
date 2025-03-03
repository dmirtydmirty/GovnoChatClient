QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_jsontests.cpp \
    ../Client/Protocol/Source/imessage.cpp \
    ../Client/Protocol/Source/packet.cpp


INCLUDEPATH += \
    ../Client/Protocol/Include/

HEADERS += \
    ../Client/Protocol/Include/imessage.h \
    ../Client/Protocol/Include/packet.h \
    ../Client/Protocol/Include/serverstatusmessage.h \
    ../Client/Protocol/Include/useridnotification.h \
    ../Client/Protocol/Include/usermessage.h
