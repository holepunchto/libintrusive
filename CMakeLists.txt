cmake_minimum_required(VERSION 3.25)

project(intrusive C)

add_library(intrusive INTERFACE)

set_target_properties(
  intrusive
  PROPERTIES
  C_STANDARD 99
)

target_sources(
  intrusive
  INTERFACE
    include/intrusive.h
    include/intrusive/list.h
    include/intrusive/queue.h
    include/intrusive/ring.h
    include/intrusive/set.h
    include/intrusive/stack.h
)

target_include_directories(
  intrusive
  INTERFACE
    include
)

install(FILES include/intrusive.h DESTINATION include)

install(DIRECTORY include/intrusive DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()
