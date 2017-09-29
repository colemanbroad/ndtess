cmake_minimum_required(VERSION 3.1)
project(ndtess CXX)

option(WITH_TESTS "Compile and provide unit tests (C++ and python)" ON)
option(WITH_CXX_TESTS "Compile and provide unit tests (C++ only)" ON)
option(WITH_PYTHON_TESTS "Compile and provide unit tests (python only)" ON)

if(NOT ${WITH_TESTS})
  set(WITH_CXX_TESTS OFF)
  set(WITH_PYTHON_TESTS OFF)
endif()

add_subdirectory(share/pybind11)
pybind11_add_module(ndtess src/ndtess.cpp)
target_compile_features(ndtess PUBLIC cxx_auto_type)


if(${WITH_CXX_TESTS})
  add_subdirectory(tests/cpp)
  include(tests/cpp/CTestLists.txt)
  set(WITH_TESTS ON)
endif()

if(${WITH_PYTHON_TESTS})
  add_subdirectory(tests/python)
  include(tests/python/CTestLists.txt)
  set(WITH_TESTS ON)
endif()


if(${WITH_TESTS})
  enable_testing()
endif()
