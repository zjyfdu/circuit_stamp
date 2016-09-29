TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
TARGET = mystamp 

SOURCES += main.cpp \
    cap.cpp \
    ind.cpp \
    isrc.cpp \
    mut.cpp \
    res.cpp \
    stamp.cpp \
    subckt.cpp \
    util.cpp \
    vsrc.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    cap.h \
    device.h \
    ind.h \
    isrc.h \
    mat.h \
    mut.h \
    res.h \
    stamp.h \
    subckt.h \
    util.h \
    vsrc.h

