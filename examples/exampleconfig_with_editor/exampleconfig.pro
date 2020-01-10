TARGET = mconfig
TEMPLATE = app
#CONFIG += MCRYPTO_LIB
CONFIG += mconfig-editors
include(../../mconfig.pri)

HEADERS += exampleconfig.h
SOURCES += main.cpp
