cmake_minimum_required(VERSION 3.1)
project(ndtess)

find_package(pybind11 REQUIRED)
pybind11_add_module(example src/ndtess.cpp)