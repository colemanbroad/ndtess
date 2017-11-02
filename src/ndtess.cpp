#ifndef NDTESS_H
#define NDTESS_H

#include <pybind11/pybind11.h>
#include "scalar_math.hpp"
#include "vector_math.hpp"

PYBIND11_MODULE(ndtess, m) {
    m.doc() = "module that performs a voronoi tesselation on ndimensional images";

    m.def("add_scalars", &ndtess::scalar::add, "A function which adds two numbers");
    m.def("add_vectors", &ndtess::vector::add, "A function which adds two numpy arrays");
}




#endif /* NDTESS_H */
