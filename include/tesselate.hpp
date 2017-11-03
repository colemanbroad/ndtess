#ifndef TESSELATE_H
#define TESSELATE_H

#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"

namespace py = pybind11;

namespace ndtess {

    namespace tesselate {

        py::array_t<double> labimg(py::array_t<double> input) {

            auto buf = input.unchecked();

            //TODO: how to create an array with the SHAPE than input?
            auto result = py::array_t<double>(input);

            return result;
        }

    };
};

#endif /* TESSELATE_H */
