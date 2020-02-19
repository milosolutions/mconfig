
find_package(Qt5 COMPONENTS REQUIRED Core Test)

add_executable(tst_mconfig submconfig.h submconfig.cpp tst_mconfig.cpp
  testdata.qrc
  $<TARGET_OBJECTS:mconfig>
)

target_include_directories(tst_mconfig PUBLIC
  $<TARGET_PROPERTY:mconfig,INCLUDE_DIRECTORIES>
)

target_link_libraries(tst_mconfig
  Qt5::Core Qt5::Test
)

add_test(tst_mconfig tst_mconfig)
