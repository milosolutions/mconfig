find_package(Qt5 COMPONENTS REQUIRED Core Test)

set(CMAKE_AUTOMOC ON)

add_executable(exampleconfig exampleconfig.h exampleconfig.cpp main.cpp)

target_link_libraries(exampleconfig mconfig
  Qt5::Core
)
