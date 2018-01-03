INCLUDEPATH += "googlemock/include"
INCLUDEPATH += "googlemock"
INCLUDEPATH += "googletest/include"
INCLUDEPATH += "googletest"
INCLUDEPATH += "../"

CONFIG += c++14 console

HEADERS += \
    ../functions.h

SOURCES += \
    main.cpp \
    googlemock/src/gmock-all.cc \
    googletest/src/gtest-all.cc


QT       += core gui
