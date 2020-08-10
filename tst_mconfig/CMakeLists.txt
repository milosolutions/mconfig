find_package(Qt5 COMPONENTS REQUIRED Core Test)

set(CMAKE_AUTOMOC ON)

add_executable(tst_mconfig submconfig.h submconfig.cpp tst_mconfig.cpp
  testdata.qrc
)

target_link_libraries(tst_mconfig mconfig
  Qt5::Core Qt5::Test
)

add_test(tst_mconfig tst_mconfig)
