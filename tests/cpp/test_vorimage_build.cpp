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


TEST_CASE_METHOD( image_fixture, "use empty heap", "[image]" ) {

    ndtess::pqueue<float> q;

    REQUIRE( data_.data() != nullptr );

    SECTION("empty heap produces non-empty result"){

        auto i = ndtess::vorimage::build(q,data_.data(),shape);
        REQUIRE( ! i.empty() );

    }

}

TEST_CASE_METHOD( image_fixture, "use synthetic dist map", "[image]" ) {

    REQUIRE( data_.data() != nullptr );

    SECTION("first pixel equal to python value"){

        auto q = ndtess::heap::build(data_.data(),shape);
        auto i = ndtess::vorimage::build(q,data_.data(),shape);
        REQUIRE( ! i.empty() );
        REQUIRE( i[0] == Approx(100.f) );

    }

}
