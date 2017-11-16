#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>

#include "catch.hpp"
#include "detail/common.hpp"
#include "fixtures.hpp"

TEST_CASE( "comply-to-python-item0", "[operator<]" ) {

    //tuple comparison in python is lexicographic
    //https://docs.python.org/3/reference/expressions.html#comparisons
    auto base = std::make_tuple(13.f,0,0,42.f);
    auto bigger = std::make_tuple(14.f,0,0,42.f);
    auto smaller = std::make_tuple(12.f,0,0,42.f);

    std::less<ndtess::item<float>> c;

    REQUIRE( c(base,bigger) );
    REQUIRE( c(smaller,base) );


}

TEST_CASE( "comply-to-python-item1", "[operator<]" ) {

    //tuple comparison in python is lexicographic
    //https://docs.python.org/3/reference/expressions.html#comparisons
    auto base = std::make_tuple(13.f,1,0,42.f);
    auto bigger = std::make_tuple(13.f,2,0,42.f);
    auto smaller = std::make_tuple(13.f,0,0,42.f);

    std::less<ndtess::item<float>> c;

    REQUIRE( c(base,bigger) );
    REQUIRE( c(smaller,base) );


}

TEST_CASE( "comply-to-python-item2", "[operator<]" ) {

    //tuple comparison in python is lexicographic
    //https://docs.python.org/3/reference/expressions.html#comparisons
    auto base = std::make_tuple(13.f,0,1,42.f);
    auto bigger = std::make_tuple(13.f,0,2,42.f);
    auto smaller = std::make_tuple(13.f,0,0,42.f);

    std::less<ndtess::item<float>> c;


    REQUIRE( c(base,bigger) );
    REQUIRE( c(smaller,base) );

}


TEST_CASE( "comply-to-python-item3", "[operator<]" ) {

    //tuple comparison in python is lexicographic
    //https://docs.python.org/3/reference/expressions.html#comparisons
    auto base = std::make_tuple(13.f,0,0,42.f);
    auto bigger = std::make_tuple(13.f,0,0,43.f);
    auto smaller = std::make_tuple(13.f,0,0,41.f);

    std::less<ndtess::item<float>> c;

    REQUIRE( c(base,bigger) );
    REQUIRE( c(smaller,base) );

}
