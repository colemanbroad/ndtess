cmake_minimum_required(VERSION 3.1)
project(ndtess CXX)

option(WITH_TESTS "Compile and provide unit tests (C++ and python)" ON)
option(WITH_CXX_TESTS "Compile and provide unit tests (C++ only)" ON)

if(NOT ${WITH_TESTS})
  set(WITH_CXX_TESTS OFF)
else()
  set(WITH_CXX_TESTS ON)
endif()

include_directories(include)
add_subdirectory(share/pybind11)

pybind11_add_module(example src/ndtess.cpp)
pybind11_add_module(ndtess src/ndtess.cpp)
target_compile_features(example PUBLIC cxx_auto_type)
target_compile_features(ndtess PUBLIC cxx_auto_type)

if(${WITH_CXX_TESTS})
  add_definitions(-g)
  add_subdirectory(tests/cpp)
  include(tests/cpp/CTestLists.txt)
  set(WITH_TESTS ON)
endif()

if(${WITH_TESTS})
  enable_testing()
endif()
