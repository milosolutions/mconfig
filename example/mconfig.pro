include(../mconfig.pri)

QT -= gui

TARGET = miloconfig
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    exampleconfig.cpp

HEADERS += \
    exampleconfig.h
