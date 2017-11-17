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

TEST_CASE( "python_says", "[operator<]" ) {

    //tuple comparison in python is lexicographic
    //https://docs.python.org/3/reference/expressions.html#comparisons
    auto lhs = std::make_tuple(1.f,10,0,100.f);
    auto rhs = std::make_tuple(1.f,9,1,100.f);

    std::less<ndtess::item<float>> c;

    REQUIRE( !c(lhs,rhs) );

    ndtess::pqueue<float> q;

    SECTION("add-to-queue"){
        q.push(lhs);
        auto t = q.top();
        REQUIRE( t == lhs );

        q.push(rhs);
        t = q.top();
        REQUIRE( t != lhs );
    }

}


TEST_CASE( "pqueue_ordering", "[operator<]" ) {

    std::priority_queue<int> ltq;

    SECTION("add"){
        ltq.push(5);
        ltq.push(1);
        ltq.push(2);
        ltq.push(0);
        REQUIRE(ltq.top() == 5);
    }


    std::priority_queue<int,std::vector<int>, std::greater<int>> gtq;

    SECTION("add"){
        gtq.push(5);
        gtq.push(1);
        gtq.push(2);
        gtq.push(0);
        REQUIRE(gtq.top() == 0);
    }

}
