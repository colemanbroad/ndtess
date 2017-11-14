#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>

#include "detail/vorimage.hpp"

#include "catch.hpp"
#include "fixtures.hpp"


TEST_CASE_METHOD( image_fixture, "create heap from image", "[image]" ) {

    ndtess::pqueue<float> q;

    REQUIRE( data_.data() != nullptr );

    SECTION("empty heap produces non-empty result"){

        auto i = ndtess::vorimage::build(q,data_.data(),shape);
        REQUIRE( ! i.empty() );

    }

}
