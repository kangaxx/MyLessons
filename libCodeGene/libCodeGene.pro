TEMPLATE = app
QT += core xml sql
CONFIG += console
DESTDIR = ../../lib

SOURCES += main.cpp \
    itemplatefile.cpp \
    imacro.cpp \
    ireadwritecodetemplates.cpp \
    ierrormsg.cpp \
    icodeelement.cpp \
    icodegenedao.cpp

HEADERS += itemplatefile.h \
    common.h \
    imacro.h \
    ireadwritecodetemplates.h \
    ierrormsg.h \
    icodeelement.h \
    icodegenedao.h

INCLUDEPATH += ../../hds

