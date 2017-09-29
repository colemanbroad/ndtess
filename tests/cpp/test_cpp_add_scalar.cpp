#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "scalar_math.hpp"

TEST_CASE( "tests on scalars", "[scalars]" ) {

    REQUIRE( ndtess::scalar::add(1,1) == 2 );
}
