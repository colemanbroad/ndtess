#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include <iostream>
#include <cstdint>
#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"

namespace py = pybind11;

namespace ndtess {

    namespace vector {

        py::array_t<double> add(py::array_t<double> input1, py::array_t<double> input2) {
            auto buf1 = input1.unchecked(), buf2 = input2.unchecked();

            if (buf1.size() != buf2.size())
                throw std::runtime_error("Input shapes must match");

            /* No pointer is passed, so NumPy will allocate the buffer */
            auto result = py::array_t<double>(buf1.size());

            auto buf3 = result.mutable_unchecked();

            double *ptr1 = (double *) buf1.data(0),
                *ptr2 = (double *) buf2.data(0),
                *ptr3 = (double *) buf3.data(0);

            const std::size_t len = input1.size();
            for (std::size_t idx = 0; idx < len; idx++)
                ptr3[idx] = ptr1[idx] + ptr2[idx];

            return result;
        }
    };

};

#endif /* VECTOR_MATH_H */
