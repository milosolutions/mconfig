find_package(Qt6 COMPONENTS REQUIRED Test)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Test)
endif()

set(CMAKE_AUTOMOC ON)

add_executable(tst_mconfig tst_mconfig.cpp)
target_link_libraries(tst_mconfig mconfig Qt::Test)

add_test(tst_mconfig tst_mconfig)
