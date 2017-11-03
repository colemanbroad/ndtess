#ifndef SCALAR_MATH_H
#define SCALAR_MATH_H

#include <iostream>

namespace ndtess {

    namespace scalar {

        int add(int i, int j) {
            std::cout << "[ndtess::scalar] hey this is adding 2 scalars with C++!\n";
            return i + j;
        }

    }

};

#endif /* SCALAR_MATH_H */
