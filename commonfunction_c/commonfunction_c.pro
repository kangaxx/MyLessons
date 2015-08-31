#TEMPLATE = app
TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += plugin
TARGET = commonfunction_c

DESTDIR = ../../lib

SOURCES += main.cpp \
    commonfunction_c.cpp

HEADERS += \
    commonfunction_c.h

INCLUDEPATH += ../../hds
