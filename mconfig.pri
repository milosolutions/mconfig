QT += core
CONFIG += c++11
DEFINES *= QT_USE_QSTRINGBUILDER

INCLUDEPATH += $$PWD

OTHER_FILES += $$PWD/README.md $$PWD/mconfig.doxyfile

HEADERS += \
    $$PWD/mbaseconfig.h \
    $$PWD/mconfig.h \
    $$PWD/mmetaconfig.h \
    $$PWD/mmetaconfigeditor.h \
    $$PWD/editors/propertyeditor.h \
    $$PWD/editors/stringeditor.h

SOURCES += \
    $$PWD/mbaseconfig.cpp \
    $$PWD/mconfig.cpp \
    $$PWD/mmetaconfig.cpp \
    $$PWD/mmetaconfigeditor.cpp \
    $$PWD/editors/propertyeditor.cpp \
    $$PWD/editors/stringeditor.cpp

DISTFILES += \
    $$PWD/AUTHORS.md

DEFINES += MCONFIG_LIB