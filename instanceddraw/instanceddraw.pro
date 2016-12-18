#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T22:05:17
#
#-------------------------------------------------

QT       += core
QT += 3dcore 3drender 3dinput 3dlogic

greaterThan(QT_MAJOR_VERSION, 4): QT += gui

TARGET = draw
TEMPLATE = app

SOURCES += main.cpp\
        window.cpp \


HEADERS  += window.h \


DISTFILES +=

RESOURCES += \
    shader.qrc

INCLUDEPATH += E:/library
