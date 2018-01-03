#-------------------------------------------------
#
# Project created by QtCreator 2017-12-28T20:37:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Planet
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp \
    circle.cpp \
    scene.cpp

HEADERS  += widget.h \
    circle.h \
    functions.h \
    scene.h

FORMS    += widget.ui


