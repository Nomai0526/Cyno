#-------------------------------------------------
#
# Project created by QtCreator 2019-07-09T19:32:06
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
RC_ICONS = logo.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cyno
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        widget.cpp \
    registerwidget.cpp \
    loginwidget.cpp \
    currentaccount.cpp \
    sessionlistitem.cpp \
    sessionwidget.cpp \
    settingswidget.cpp \
    searchcontactswidget.cpp \
    searchresultitem.cpp \
    contactslistitem.cpp \
    contactswidget.cpp \
    historywidget.cpp \
    mainwidget.cpp \
    clientsqladmin.cpp \
    sessionlistitemofmain.cpp

HEADERS  += widget.h \
    registerwidget.h \
    loginwidget.h \
    currentaccount.h \
    sessionlistitem.h \
    sessionwidget.h \
    settingswidget.h \
    searchcontactswidget.h \
    searchresultitem.h \
    contactslistitem.h \
    contactswidget.h \
    historywidget.h \
    mainwidget.h \
    clientsqladmin.h \
    sessionlistitemofmain.h

RESOURCES += \
    cynoresources.qrc \
    resources.qrc \
    cynoresources.qrc

DISTFILES += \
    resources/defaultAvatar.jpg \
    resources/defaultBack.jpg \
    resources/defaultBack2.jpg \
    resources/sessionAvatar.jpg \
    resources/defaultMainBack.jpg
