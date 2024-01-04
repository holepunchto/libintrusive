cmake_minimum_required(VERSION 3.25)

project(intrusive C)

add_library(intrusive OBJECT)

set_target_properties(
  intrusive
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
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
  PRIVATE
    src/list.c
    src/queue.c
    src/ring.c
    src/set.c
    src/stack.c
)

target_include_directories(
  intrusive
  PUBLIC
    include
)

add_library(intrusive_shared SHARED)

set_target_properties(
  intrusive_shared
  PROPERTIES
  OUTPUT_NAME intrusive
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries(
  intrusive_shared
  PUBLIC
    intrusive
)

add_library(intrusive_static STATIC)

set_target_properties(
  intrusive_static
  PROPERTIES
  OUTPUT_NAME intrusive
  PREFIX lib
)

target_link_libraries(
  intrusive_static
  PUBLIC
    intrusive
)

install(TARGETS intrusive_shared intrusive_static)

install(FILES include/intrusive.h DESTINATION include)

install(DIRECTORY include/intrusive DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()
