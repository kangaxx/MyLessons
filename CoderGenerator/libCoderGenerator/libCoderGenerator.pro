
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dnifgenerator.cpp

HEADERS += \
    dnifgenerator.h

QMAKE_CXXFLAGS += -std=c++0x
