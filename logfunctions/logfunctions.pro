#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T16:25:23
#
#-------------------------------------------------


QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = logfunctions
DESTDIR = $(QM_ROOT)/lib
TEMPLATE = lib
CONFIG += staticlib

#TEMPLATE = app

SOURCES += UserLogInfo.cpp \
    SystemLogInfo.cpp \
    IReadWriteUserLog.cpp \
    IReadWriteSystemLog.cpp


HEADERS += $(QM_SRC)/hds/logInclude.h \
           $(QM_SRC)/hds/ILogInfo.h

LIBS += $(QM_ROOT)/lib -lSqlFunctions

INCLUDEPATH += $(QM_SRC)/hds

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXX =  /home/gxx/Codes/GCC4.8.0/build/bin/g++
QMAKE_LINK = /home/gxx/Codes/GCC4.8.0/build/bin/g++
