#ifndef TESSELATE_H
#define TESSELATE_H

#include <queue>

#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"

namespace py = pybind11;

namespace ndtess {

    namespace tesselate {

        py::array_t<double> labimg_impl(const py::array_t<double>& input,
                                        const py::array_t<double>& distimg) {

            auto mbuf = input.unchecked();

            //TODO: how to create an array with the SHAPE than input?
            auto result = py::array_t<double>(input);

            std::vector<std::size_t> shape(input.ndim(), 0);
            int c = 0;
            for(std::size_t & el: shape)
                el = input.shape(c++);

            //initialize heap queue

            return result;

        }

        py::array_t<double> labimg(const py::array_t<double>& input) {

            auto distimg = py::array_t<double>(input);
            auto mbuf = distimg.mutable_unchecked();

            std::fill(&mbuf[0], &mbuf[0] + distimg.size(),0.);

            auto result = labimg_impl(input, distimg);

            return result;
        }

    };
};

#endif /* TESSELATE_H */
