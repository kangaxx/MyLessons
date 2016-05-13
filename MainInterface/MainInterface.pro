 #-------------------------------------------------
 #Copyright@2013 上海青凤致远地球物理地质勘探科技有限公司IT部
 #All Right Reserved
 #
 #简    介：QModeling 程序主界面。
 #作    者：
 #完成日期：
 #版 本 号：
 #-------------------------------------------------


QT       += core gui opengl\
            xml\
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QModeling
DESTDIR = $(QM_ROOT)/bin
TEMPLATE = app

LIBS += -L$(QM_ROOT)/lib -llogBar -lToolsAlgo  -lSideBar -lCommonFunctions -lSqlFunctions -lcommonfunction_c
LIBS += -L$(QM_ROOT)/lib -lcommonfunction_qt -lProjectManagerSo -lAssistant -L/home/apps/mpi_gnu/lib -lmpich -lmpichcxx

SOURCES += main.cpp\
        mainwindow.cpp \
    xmlfilefunctions.cpp \
    buttonthreestatus.cpp

HEADERS  += mainwindow.h \
    commonfunctions.h \
    xmlfilefunctions.h \
    buttonthreestatus.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    system.xml \


INCLUDEPATH += $(QM_ROOT)/hds /home/apps/mpi_gnu/include

QMAKE_CXXFLAGS += -std=c++11 
QMAKE_CXXFLAGS += -fopenmp 

QMAKE_CXX = /home/gxx/Codes/GCC4.8.0/build/bin/g++
QMAKE_LINK = /home/apps/mpi_gnu/bin/mpic++ -fopenmp

DEFINES += "INT_LICENSE_TYPE=1"  # 0 , NO LICENSE; 1 , DATE; 2 , OTHERS
DEFINES += "INT_LICENSE_DATE_BEGIN=2001" # yyddd  , yy表示年份从2015开始 dd表示天数，一年365/366天
DEFINES += "INT_LICENSE_DATE_DAYS=1" # 有效期限
#LIBS += -L/usr/local/lib -lGLU     -lglut
