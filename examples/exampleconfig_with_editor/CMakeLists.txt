if (mconfig-editors)
  set(CMAKE_AUTOMOC ON)
  #set(mconfig-editors ON)
  add_executable(exampleconfig_with_editor exampleconfig.h main.cpp)
  target_link_libraries(exampleconfig_with_editor mconfig)

else()
  message("This example requires mconfig-editors build option to be enabled.")
endif()
