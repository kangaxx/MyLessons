QT += core gui sql xml widgets
#TEMPLATE = app  #for unit test
TEMPLATE = lib
CONFIG += console

DESTDIR = $(QM_ROOT)/lib

SOURCES += main.cpp \
    logshmcontrol.cpp

INCLUDEPATH += $(QM_ROOT)/hds
LIBS += -L$(QM_ROOT)/lib -lcommonfunction_c -llogfunctions

HEADERS += \
    ../../hds/logshmcontrol.h

QMAKE_CXXFLAGS += -std=c++11

QMAKE_CXX =  /home/gxx/Codes/GCC4.8.0/build/bin/g++
QMAKE_LINK = /home/gxx/Codes/GCC4.8.0/build/bin/g++
