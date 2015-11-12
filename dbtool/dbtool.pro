#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T15:09:22
#
#-------------------------------------------------

QT       += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dbtool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
INCLUDEPATH += ../../hds
LIBS += -L$(QM_ROOT)/lib -lcommonfunction_c

QMAKE_CXXFLAGS += -std=c++11
