#ifndef HEAPQUEUE_H
#define HEAPQUEUE_H

#include <tuple>
#include <vector>
#include <queue>
#include <numeric>
#include <iterator>

namespace ndtess {

    namespace heap {

        template <typename label_t>
        using item = std::tuple<float,std::size_t, std::size_t,label_t>;




        template <typename T>
        static std::priority_queue<item<T>> build(const T* _lab,
                                               const std::vector<std::size_t>& _shape,
                                               const float* _dist){

            using queue = std::priority_queue<item<T>>;

            const T nil = 0;
            queue q;
            static constexpr int offsets_x[4] = {-1,1,0,0};
            static constexpr int offsets_y[4] = {0,0,-1,1};

            for(int off = 0;off < 4;++off){
                std::size_t y_lo = offsets_y[off] < 0 ? std::abs(offsets_y[off]) : 0;
                std::size_t y_hi = offsets_y[off] > 0 ? _shape[1] - offsets_y[off] : _shape[1];

                std::size_t x_lo = offsets_x[off] < 0 ? std::abs(offsets_x[off]) : 0;
                std::size_t x_hi = offsets_x[off] > 0 ? _shape[0] - offsets_x[off] : _shape[0];

                for(std::size_t y = y_lo;y < y_hi;++y){
                    for(std::size_t x = x_lo;x < x_hi;++x){
                        std::size_t pix_offset = y*_shape[0] + x;
                        if(!(_lab[pix_offset]!=nil))
                            continue;
                        float res = 1. + std::abs(_dist[pix_offset] + _dist[(y+offsets_y[off])*_shape[0] + (x+offsets_x[off])]);
                        q.push(std::make_tuple(res,
                                               y+offsets_y[off],
                                               x+offsets_x[off],
                                               _lab[pix_offset]));
                    }
                }
            }


            return q;

        }


         template <typename T>
        static std::priority_queue<item<T>> build(const T* _lab,
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
