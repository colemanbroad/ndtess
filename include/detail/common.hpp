#ifndef COMMON_H
#define COMMON_H

#include <tuple>
#include <vector>
#include <queue>
#include <cstdint>

namespace ndtess {

    template <typename T>
    using item = std::tuple<float,std::size_t, std::size_t,T>;

    template <typename T>
    struct compare {
        bool operator()(const item<T>& _lhs, const item<T>& _rhs){
            return std::get<0>(_lhs) < std::get<0>(_rhs);
        }
    };

    template <typename T>
    using pqueue = std::priority_queue<item<T>,
                                       std::vector<item<T> >,
                                       compare<T>
                                       >;

    template <typename T>
    using pvec = std::vector< item<T> >;



};

#endif /* COMMON_H */
