#ifndef TESSELATE_H
#define TESSELATE_H

#include "detail/heapqueue.hpp"
#include "detail/vorimage.hpp"

#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"

#include <queue>

namespace py = pybind11;

namespace ndtess {

    namespace tesselate {

        template <typename T>
        py::array_t<double> labimg_impl(const py::array_t<double>& input,
                                        const py::array_t<T>& distimg) {

            auto mbuf = input.unchecked();

            //TODO: how to create an array with the SHAPE than input?
            auto result = py::array_t<double>(input);

            std::vector<std::size_t> shape(input.ndim(), 0);
            int c = 0;
            for(std::size_t & el: shape)
                el = input.shape(c++);

            //initialize heap queue
            const double* in = reinterpret_cast<const double*>(input.unchecked().data(0));

            double* out = reinterpret_cast<double*>(result.mutable_unchecked().mutable_data(0));

            const T* di = reinterpret_cast<const T*>(distimg.unchecked().data(0));
            auto heap = heap::build(in,
                                    shape,
                                    di);

            vorimage::build(out,heap,in,shape,di);

            return result;

        }

        py::array_t<double> labimg(const py::array_t<double>& input) {

            auto distimg = py::array_t<float>(input);
            auto mbuf = distimg.mutable_unchecked();

            std::fill(&mbuf[0], &mbuf[0] + distimg.size(),0.);

            auto result = labimg_impl(input, distimg);

            return result;
        }

    };
};

#endif /* TESSELATE_H */
