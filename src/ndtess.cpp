#ifndef NDTESS_H
#define NDTESS_H

#include <pybind11/pybind11.h>
#include "scalar_math.hpp"
#include "vector_math.hpp"
#include "tesselate.hpp"

PYBIND11_MODULE(ndtess, m) {
    m.doc() = "module that performs a voronoi tesselation on ndimensional images";

    //these are for playing around with the pybind11 syntax
    m.def("add_scalars", &ndtess::scalar::add, "A function which adds two numbers");
    m.def("add_vectors", &ndtess::vector::add, "A function which adds two numpy arrays");

    //
    m.def("tessellate_labimg", &ndtess::tesselate::labimg, "the C++ implementation of the voronoi tesselation");
}




#endif /* NDTESS_H */
