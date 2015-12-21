#-------------------------------------------------
#
# Project created by QtCreator 2015-10-09T13:02:27
#
#-------------------------------------------------

QT       += core gui widgets winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Offline_Launcher
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    systemtray.cpp \
    firewall.cpp \
    config.cpp \
    program.cpp \
    programs.cpp

HEADERS  += widget.h \
    systemtray.h \
    firewall.h \
    config.h \
    program.h \
    programs.h

FORMS    += widget.ui

RESOURCES += \
    offline_launcher.qrc

CONFIG += c++11
