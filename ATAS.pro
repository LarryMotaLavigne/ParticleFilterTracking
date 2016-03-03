#-------------------------------------------------
#
# Project created by QtCreator 2015-01-15T15:10:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATAS
TEMPLATE = app

CONFIG += console\
          c++11\

SOURCES += main.cpp\
    tools.cpp \
    model/frame.cpp \
    model/video.cpp \
    controller/c_video.cpp \
    view/mainwindow.cpp \
    controller/c_algorithm.cpp \
    model/node.cpp \
    model/edge.cpp \
    model/particle.cpp \
    model/object.cpp \
    model/graph.cpp \
    view/helpwindow.cpp

HEADERS  += tools.h \
    model/frame.h \
    model/video.h \
    controller/c_video.h \
    view/mainwindow.h \
    controller/c_algorithm.h \
    model/node.h \
    model/edge.h \
    model/particle.h \
    model/object.h \
    model/graph.h \
    view/helpwindow.h

INCLUDEPATH += C:\opencv-mingw\install\include
LIBS += -L"C:/opencv-mingw/install/x86/mingw/bin"
LIBS += -lopencv_core2410 -lopencv_highgui2410 -lopencv_imgproc2410 -lopencv_video2410

FORMS+= view/mainwindow.ui \
    view/helpwindow.ui

RESOURCES += \
    resources.qrc

