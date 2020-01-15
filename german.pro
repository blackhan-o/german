#-------------------------------------------------
#
# Project created by QtCreator 2019-09-19T17:29:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = german
TEMPLATE = app

QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += main.cpp\
        mainwindow.cpp \
    error.cpp \
    slavyanski.cpp

HEADERS  += mainwindow.h \
    maps.h

FORMS    += mainwindow.ui
