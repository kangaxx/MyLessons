#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T13:25:40
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = _3LayerLesson
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dnmodel.cpp \
    dndao.cpp \
    dnserver.cpp

HEADERS  += mainwindow.h \
    dnmodel.h \
    dndao.h \
    dnserver.h

FORMS    += mainwindow.ui
