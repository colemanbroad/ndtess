#include "catch.hpp"
#include "scalar_math.hpp"

TEST_CASE( "tests on scalars", "[scalars]" ) {

    REQUIRE( ndtess::scalar::add(1,1) == 2 );
}
