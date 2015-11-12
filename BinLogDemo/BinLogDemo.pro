TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $(QM_ROOT)/bin
SOURCES += main.cpp \
    logfunctions.cpp


INCLUDEPATH += ../../hds
include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    logfunctions.h

