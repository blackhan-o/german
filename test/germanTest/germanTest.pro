QT       += core

QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = germanTest
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


INCLUDEPATH += "googletest/include"
INCLUDEPATH += "googletest/"
INCLUDEPATH += "../../"

SOURCES += main.cpp \
    googletest/src/gtest.cc \
    googletest/src/gtest-all.cc \
    googletest/src/gtest-death-test.cc \
    googletest/src/gtest-filepath.cc \
    googletest/src/gtest-matchers.cc \
    googletest/src/gtest-port.cc \
    googletest/src/gtest-printers.cc \
    googletest/src/gtest-test-part.cc \
    googletest/src/gtest-typed-test.cc \
    ../../error.cpp \
    ../../transform.cpp

HEADERS += \
    ../../maps.h
