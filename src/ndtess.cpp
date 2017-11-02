#include <pybind11/pybind11.h>
#include "scalar_math.hpp"

PYBIND11_MODULE(ndtess, m) {
    m.doc() = "module that performs a voronoi tesselation on ndimensional images";

    m.def("add_scalars", &ndtess::scalar::add, "A function which adds two numbers");
    m.def("add_vectors", &ndtess::scalar::add_vectors, "A function which adds two numpy numbers");
}
