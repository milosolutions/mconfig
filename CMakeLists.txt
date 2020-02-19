
project(mconfig
  VERSION 0.0.1
  DESCRIPTION "Milo Config"
  LANGUAGES CXX
)

find_package(Qt5 COMPONENTS REQUIRED Core)

set(SOURCES mbaseconfig.h mbaseconfig.cpp mconfig.h mconfig.cpp
  mmetaconfig.h mmetaconfig.cpp
)

option (mconfig-editors "Build GUI (QtWidgets) config editors" OFF)

if(mconfig-editors)
  find_package(Qt5 COMPONENTS REQUIRED Widgets)
  list(APPEND SOURCES editors/mmetaconfigeditor.h editors/mmetaconfigeditor.cpp
    editors/propertyeditor.h editors/propertyeditor.cpp
    editors/stringeditor.h editors/stringeditor.cpp)
endif(mconfig-editors)

set(OTHER_FILES README.md AUTHORS.md mconfig.doxyfile)

add_library(mconfig OBJECT ${SOURCES} ${OTHER_FILES})

target_include_directories(mconfig
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# Defines
target_compile_definitions(mconfig PUBLIC MCONFIG_LIB)

if (mconfig-editors)
  target_link_libraries(mconfig
    Qt5::Core
    Qt5::Widgets
  )
else (mconfig-editors)
  target_link_libraries(mconfig
    Qt5::Core
  )
endif(mconfig-editors)

add_subdirectory(tst_mconfig)
