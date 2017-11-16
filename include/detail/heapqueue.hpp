#ifndef HEAPQUEUE_H
#define HEAPQUEUE_H

#include "detail/common.hpp"

#include <iomanip>
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

            std::int64_t x2 = 0;
            std::int64_t y2 = 0;
            static constexpr T epsilon = std::numeric_limits<T>::epsilon();

            pvec<T> under_heap;
            queue q;

#ifdef NDTESS_TRACE
            std::cout.precision(1);
#endif
            for(std::int64_t y = 0;y < _shape[ndtess::in_y];++y){
                for(std::int64_t x = 0;x < _shape[ndtess::in_x];++x){

                    std::size_t pix_offset = y*_shape[ndtess::in_x] + x;
                    if(std::abs(_lab[pix_offset]) < epsilon)
                        continue;

                    for(int off = 0;off < 4;++off){

                        x2 = x + ndtess::offsets_x[off];
                        y2 = y + ndtess::offsets_y[off];
                        if(!( x2 >= 0 && x2 < _shape[ndtess::in_x] && y2 >= 0 && y2 < _shape[ndtess::in_y] ))
                            continue;

                        auto d1 = _dist[pix_offset];
                        auto d2 = _dist[(y2)*_shape[ndtess::in_x] + (x2)];
                        auto res = std::abs(d1 + d2) + 1.f;

#ifdef NDTESS_TRACE
                        std::cout << "<> "
                                  << "(" << std::setw(3) << y
                                  << std::setw(3) << x
                                  << ")"
                                  << std::setw(4) << d1 << " "
                                  << "(" << std::setw(3) << y2
                                  << std::setw(3) << x2
                                  << ")"
                                  << std::setw(4) << d2
                                  << " " << _lab[pix_offset];
#endif
                        q.push(std::make_tuple(res,
                                               x2,
                                               y2,
                                               _lab[pix_offset]));
#ifdef NDTESS_TRACE
                        auto t = q.top();
                        std::cout << " -> "
                                  << std::get<0>(t) << ", "
                                  << std::get<1>(t) << ", "
                                  << std::get<2>(t) << ", "
                                  << std::get<3>(t) << " " << q.size()
                                  << "\n";
#endif
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
