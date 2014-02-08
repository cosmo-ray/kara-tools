TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS +=  -L$$PWD/lib/ -lavdevice -lavformat -lavcodec -lavutil -lswscale
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

SOURCES += \
    autoass2toy.c

