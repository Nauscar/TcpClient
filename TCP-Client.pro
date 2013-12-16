#-------------------------------------------------
#
# Project created by QtCreator 2013-12-16T14:03:34
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = TCP-Client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    applicationui.cpp \
    tcpclient.cpp

HEADERS += \
    applicationui.h \
    tcpclient.h
