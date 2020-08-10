find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)

set(CMAKE_AUTOMOC ON)
set(mconfig-editors ON)

add_executable(exampleconfig_with_editor exampleconfig.h main.cpp)

target_link_libraries(exampleconfig_with_editor mconfig
  Qt5::Core Qt5::Gui Qt5::Widgets
)
