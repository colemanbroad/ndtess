#ifndef VORIMAGE_H
#define VORIMAGE_H

#include <tuple>
#include <vector>
#include <queue>
#include <numeric>
#include <iterator>

#include "detail/heapqueue.hpp"
#include "detail/common.hpp"

namespace ndtess {

    namespace vorimage {


        template <typename T>
        static std::vector<T> build(pqueue<T>& _heap,
                                    const T* _lab,
                                    const std::vector<std::size_t>& _shape,
                                    const float* _dist){

            const std::size_t len = std::accumulate(std::begin(_shape),
                                                    std::end(_shape),
                                                    1,
                                                    std::multiplies<std::size_t>()
                );

            std::vector<T> value(len,0);
            return value;

        }


         template <typename T>
         static std::vector<T> build(pqueue<T>& _heap,
                                     const T* _lab,
                                     const std::vector<std::size_t>& _shape){

            const std::size_t len = std::accumulate(std::begin(_shape),
                                                    std::end(_shape),
                                                    1,
                                                    std::multiplies<std::size_t>()
                );
            std::vector<float> dist(len,0.f);

            return build<T>(_heap,_lab, _shape,dist.data());

        }
    }
}

#endif /* VORIMAGE_H */
