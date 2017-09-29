#include <pybind11/pybind11.h>
#include "scalar_math.hpp"

PYBIND11_MODULE(ndtess, m) {
    m.doc() = "simple function to add two scalars";
    m.def("add_scalars", &ndtess::scalar::add, "A function which adds two numbers");
}
