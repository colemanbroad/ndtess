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

            static constexpr T epsilon = std::numeric_limits<T>::epsilon();
            const std::size_t len = std::accumulate(std::begin(_shape),
                                                    std::end(_shape),
                                                    1,
                                                    std::multiplies<std::size_t>()
                );

            std::vector<T> value(_lab, _lab + len);

            if(_heap.empty() || !len)
                return value;

            float dist = 0;
            std::size_t x = 0;
            std::size_t y = 0;
            std::size_t offset  = 0;
            std::size_t offset2 = 0;

            T label = 0;

            //FOR LATER: check if this cache miss due to first jumping in y and then jumping in x
            //           needs some attention
            static constexpr int offsets_y[4] = {-1,1,0,0};
            static constexpr int offsets_x[4] = {0,0,-1,1};
            std::int64_t x2 = 0;
            std::int64_t y2 = 0;


            while(!_heap.empty()){

                std::tie(dist,x,y,label) = _heap.top();_heap.top();

                offset = y*_shape[1]+x;
                if(std::abs(value[offset]) > epsilon)
                    continue;

                value[offset] = label;

                for(int off = 0;off < 4;++off){
                    x2 = x + offsets_x[off];
                    y2 = y + offsets_y[off];
                    if(!( x2 >= 0 && x2 < _shape[1] && y2 >= 0 && y2 < _shape[0] ))
                        continue;

                    offset2 = y2*_shape[1]+x2;
                    T newlabel = value[offset2];
                    if(newlabel <= epsilon){
                        auto d1 = _dist[offset];
                        auto d2 = _dist[offset2];
                        auto newdist = dist + std::abs(d1+d2) + 1.;
                        _heap.push(std::make_tuple(newdist,
                                                   x2,
                                                   y2,
                                                   label));

                    }

                }
            }

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
