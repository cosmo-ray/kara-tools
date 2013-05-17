#-------------------------------------------------
#
# Project created by QtCreator 2013-02-11T15:38:36
#
#-------------------------------------------------

QT       += core gui phonon


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = asraf
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 

#QMAKE_LFLAGS += -static-libgcc
LIBS +=  -L/usr/lib

SOURCES += main.cpp\
        mainwindow.cpp\
        Media.cpp\
        core.cpp

HEADERS  += mainwindow.hh \
            core.hh

