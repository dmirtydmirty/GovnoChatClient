QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_jsontests.cpp \
            ../Client/imessage.cpp

HEADERS += ../Client/serverstatusmessage.h \
            ../Client/imessage.h \
            ../Client/useridnotification.h \
            ../Client/usermessage.h
