#-------------------------------------------------
#
# Project created by QtCreator 2012-04-11T14:08:46
#
#-------------------------------------------------

QT       += core gui

TARGET = 2DLightRender
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    render.cpp \
    raytracer.cpp \
    preview.cpp \
    data.cpp \
    rmath.cpp \
    bresenhamgrid.cpp

HEADERS  += mainwindow.h \
    render.h \
    raytracer.h \
    preview.h \
    data.h \
    rmath.h \
    bresenhamgrid.h

FORMS    += mainwindow.ui

CONFIG   += -Wall -O2 -st

LIBS += -fopenmp

QMAKE_CXXFLAGS += -fopenmp
