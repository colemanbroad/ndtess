#ifndef COMMON_H
#define COMMON_H

#include <tuple>
#include <vector>
#include <array>
#include <queue>
#include <cstdint>

namespace ndtess {

    template <typename T>
    using item = std::tuple<float,std::size_t, std::size_t,T>;

    template <typename T>
    using pqueue = std::priority_queue<item<T>,
                                       std::vector<item<T> >,
                                       std::greater<item<T>>
                                       >;

    template <typename T>
    using pvec = std::vector< item<T> >;


    //FOR LATER: check if this cache miss due to first jumping in y and then jumping in x
    //           needs some attention
    static constexpr std::array<int,4> offsets_y = {-1,1,0,0};
    static constexpr std::array<int,4> offsets_x = {0,0,-1,1};

    static const int nrows = 0;
    static const int ncols = 1;

    static const int in_y = nrows;
    static const int in_x = ncols;

};

#endif /* COMMON_H */
