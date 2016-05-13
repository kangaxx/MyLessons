QT += core sql xml widgets
TEMPLATE = app
CONFIG += console

DESTDIR = $(QM_ROOT)/bin
SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()
INCLUDEPATH += $(QM_ROOT)/hds
LIBS += -L$(QM_ROOT)/lib -lcommonfunction_c -llogfunctions -llogShmControl -lSqlFunctions
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXX =  /home/gxx/Codes/GCC4.8.0/build/bin/g++
QMAKE_LINK = /home/gxx/Codes/GCC4.8.0/build/bin/g++
