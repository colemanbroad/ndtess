cmake_minimum_required(VERSION 3.1)
project(ndtess CXX)

add_subdirectory(share/pybind11)
pybind11_add_module(example src/ndtess.cpp)
