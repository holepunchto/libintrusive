cmake_minimum_required(VERSION 4.0)

find_package(cmake-prelude REQUIRED PATHS node_modules/cmake-prelude)
find_package(cmake-test REQUIRED PATHS node_modules/cmake-test)

project(intrusive LANGUAGES C VERSION 0.0.0)

add_library_targets(
  intrusive
  HEADERS
    include/intrusive.h
    include/intrusive/list.h
    include/intrusive/queue.h
    include/intrusive/ring.h
    include/intrusive/set.h
    include/intrusive/stack.h
  FEATURES
    c_std_99
  SOURCES NONE
)

add_test_subdirectory(test)
