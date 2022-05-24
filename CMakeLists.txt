if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif ()

cmake_minimum_required(VERSION 3.16.0)

project(mconfig
  VERSION 0.0.1
  DESCRIPTION "Milo Config"
  LANGUAGES CXX
)

find_package(Qt6 COMPONENTS REQUIRED Core)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core)

set(CMAKE_AUTOMOC ON)

set(SOURCES mbaseconfig.h mbaseconfig.cpp mconfig.h mconfig.cpp)

option(mconfig-editors "MConfig: Build GUI (QtWidgets) config editors" OFF)

if(mconfig-editors)
  find_package(Qt6 COMPONENTS REQUIRED Core Gui Widgets)
  if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Gui Widgets)
  list(APPEND SOURCES
    mmetaconfig.h mmetaconfig.cpp
    editors/mmetaconfigeditor.h editors/mmetaconfigeditor.cpp
    editors/propertyeditor.h editors/propertyeditor.cpp
    editors/stringeditor.h editors/stringeditor.cpp)
endif(mconfig-editors)

set(OTHER_FILES README.md AUTHORS.md mconfig.doxyfile)

add_library(mconfig STATIC ${SOURCES} ${OTHER_FILES})

target_include_directories(mconfig
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Defines
target_compile_definitions(mconfig PUBLIC MCONFIG_LIB)

option(mconfig-crypto "MConfig: Build with encryption functions" OFF)
if(mconfig-crypto)
  message("MConfig: using encryption library")
  target_compile_definitions(mconfig PRIVATE CRYPTED_CONFIG)
  target_link_libraries(mconfig mcrypto)
endif(mconfig-crypto)

target_link_libraries(mconfig PUBLIC Qt::Core)
if (mconfig-editors)
  target_link_libraries(mconfig PUBLIC
    Qt::Gui
    Qt::Widgets
  )
endif(mconfig-editors)

# TODO tests are temporarily disabled
#add_subdirectory(tst_mconfig)
#add_subdirectory(examples/exampleconfig)
#add_subdirectory(examples/exampleconfig_with_editor)
