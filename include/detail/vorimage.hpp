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
        static void build(T* result,
                          pqueue<T>& _heap,
                          const T* _lab,
                          const std::vector<std::size_t>& _shape,
                          const float* _dist){

            static constexpr T epsilon = std::numeric_limits<T>::epsilon();
            const std::size_t len = std::accumulate(std::begin(_shape),
                                                    std::end(_shape),
                                                    1,
                                                    std::multiplies<std::size_t>()
                );

            // std::vector<T> value(_lab, _lab + len);

            if(_heap.empty() || !len)
                return;

            float dist = 0;
            std::size_t x = 0;
            std::size_t y = 0;
            std::size_t offset  = 0;
            std::size_t offset2 = 0;

            T label = 0;

            std::int64_t x2 = 0;
            std::int64_t y2 = 0;


            while(!_heap.empty()){

                std::tie(dist,y,x,label) = _heap.top();_heap.pop();

                offset = y*_shape[ndtess::in_x]+x;
                if(std::abs(result[offset]) > epsilon)
                    continue;

                result[offset] = label;

                for(int off = 0;off < 4;++off){
                    x2 = x + ndtess::offsets_x[off];
                    y2 = y + ndtess::offsets_y[off];
                    if(!( x2 >= 0 && x2 < _shape[ndtess::in_x] && y2 >= 0 && y2 < _shape[ndtess::in_y] ))
                        continue;

                    offset2 = y2*_shape[ndtess::in_x]+x2;
                    T newlabel = result[offset2];
                    if(newlabel <= epsilon){
                        auto d1 = _dist[offset];
                        auto d2 = _dist[offset2];
                        auto newdist = dist + std::abs(d1+d2) + 1.;
                        _heap.push(std::make_tuple(newdist,
                                                   y2,
                                                   x2,
                                                   label));

                    }

                }
            }

            return ;

        }


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

            std::vector<T> value(_lab, _lab + len);

            build<T>(value.data(),_heap,_lab,_shape,_dist);

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
