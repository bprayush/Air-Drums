#-------------------------------------------------
#
# Project created by QtCreator 2017-03-04T09:58:56
#
#-------------------------------------------------

QT       += core gui \
            serialport\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    arduinoserial.cpp

HEADERS  += mainwindow.h \
    arduinoserial.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc \
    res.qrc
