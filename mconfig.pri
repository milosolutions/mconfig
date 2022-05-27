QT *= core
CONFIG *= c++11
DEFINES *= QT_USE_QSTRINGBUILDER
#uncomment it if you want encryption
#DEFINES *= MCRYPTO_LIB

INCLUDEPATH *= $$PWD

OTHER_FILES *= $$PWD/README.md $$PWD/mconfig.doxyfile

HEADERS *= \
    $$PWD/mbaseconfig.h \
    $$PWD/mconfig.h \
    $$PWD/mmetaconfig.h

SOURCES *= \
    $$PWD/mbaseconfig.cpp \
    $$PWD/mconfig.cpp \
    $$PWD/mmetaconfig.cpp

mconfig-crypto {
    # TODO check if mcrypto library is available
    message("MConfig: using encryption library")
    DEFINES += ENCRYPTED_CONFIG
}

mconfig-editors {
QT *= gui widgets
HEADERS *= \
    $$PWD/editors/mmetaconfigeditor.h \
    $$PWD/editors/propertyeditor.h \
    $$PWD/editors/stringeditor.h

SOURCES *= \
    $$PWD/editors/mmetaconfigeditor.cpp \
    $$PWD/editors/propertyeditor.cpp \
    $$PWD/editors/stringeditor.cpp
}

DISTFILES *= \
    $$PWD/AUTHORS.md

DEFINES *= MCONFIG_LIB
