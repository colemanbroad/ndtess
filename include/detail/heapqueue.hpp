#ifndef HEAPQUEUE_H
#define HEAPQUEUE_H

#include "detail/common.hpp"

#include <tuple>
#include <vector>
#include <queue>
#include <numeric>
#include <iterator>


namespace ndtess {

    namespace heap {


        template <typename T>
        static pqueue<T> build(const T* _lab,
                             const std::vector<std::size_t>& _shape,
                             const float* _dist){

            using local_item = item<T>;
            using queue = pqueue<T>;
            using valloc = typename std::vector<local_item>::allocator_type;

            const std::size_t len = std::accumulate(std::begin(_shape),
                                                    std::end(_shape),
                                                    1,
                                                    std::multiplies<std::size_t>()
                );

            const T nil = 0;

            //FOR LATER: check if this cache miss due to first jumping in y and then jumping in x
            //           needs some attention
            static constexpr int offsets_y[4] = {-1,1,0,0};
            static constexpr int offsets_x[4] = {0,0,-1,1};

            std::int64_t x2 = 0;
            std::int64_t y2 = 0;
            static constexpr T epsilon = std::numeric_limits<T>::epsilon();

            compare<T> lc;
            pvec<T> under_heap;
            queue q(lc);
            std::cout.precision(1);
            for(std::int64_t y = 0;y < _shape[1];++y){
                for(std::int64_t x = 0;x < _shape[0];++x){

                    std::size_t pix_offset = y*_shape[1] + x;
                    if(std::abs(_lab[pix_offset]) < epsilon)
                        continue;

                    for(int off = 0;off < 4;++off){

                        x2 = x + offsets_x[off];
                        y2 = y + offsets_y[off];
                        if(!( x2 >= 0 && x2 < _shape[1] && y2 >= 0 && y2 < _shape[0] ))
                            continue;

                        float res = 1. + std::abs(_dist[pix_offset] + _dist[(y2)*_shape[1] + (x2)]);
                        q.push(std::make_tuple(res,
                                               x2,
                                               y2,
                                               _lab[pix_offset]));
                    }
                }
            }

            return q;

        }


         template <typename T>
         static pqueue<T> build(const T* _lab,
                                const std::vector<std::size_t>& _shape){

            const std::size_t len = std::accumulate(std::begin(_shape),
                                                    std::end(_shape),
                                                    1,
                                                    std::multiplies<std::size_t>()
                );
            std::vector<float> dist(len,0.f);

            return build<T>(_lab, _shape,dist.data());

        }
    }
}

#endif /* HEAPQUEUE_H */
