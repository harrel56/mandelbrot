#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T13:39:10
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mandelbrot
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    myview.cpp \
    controlwidget.cpp

HEADERS  += widget.h \
    myview.h \
    controlwidget.h

FORMS    += widget.ui
