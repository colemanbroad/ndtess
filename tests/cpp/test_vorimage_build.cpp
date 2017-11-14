#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>

#include "detail/heapqueue.hpp"

#include "catch.hpp"
#include "fixtures.hpp"


TEST_CASE_METHOD( image_fixture, "fixture data correct", "[image]" ) {

    REQUIRE( data_.data() != nullptr );
    REQUIRE( data_[0] < 1.f );

    SECTION("small rectangle (x,y) = [6:11,2:5] was set"){
        REQUIRE( data_[13*shape[1]+2] != 0.f );
        REQUIRE( data_[13*shape[1]+2] == 42.f );
    }

    SECTION("small circle at (24,24) with radius 4"){
        REQUIRE( data_[2*shape[1]+12] != 0.f );
        REQUIRE( data_[2*shape[1]+12] == 100.f );
    }
}



TEST_CASE( "create heap from vector", "[any]" ) {

    const std::vector<float> nums = {5.f,  1.f, 7.f, 3.f};

    SECTION("make_heap gives same root as python example"){

        auto data = nums;
        std::make_heap(std::begin(data),std::end(data));
        REQUIRE( data.front() == Approx( 7.f ));

    }

    const std::vector<int>   foo  = {50, 70, 10, 30};

    SECTION("make_heap gives same root as python example with tuple"){

        std::vector<std::tuple<float,int> >   data(nums.size());
        std::transform(std::begin(nums),std::end(nums),
                       std::begin(foo),
                       std::begin(data),
                       [](const float& _lhs, const int& _rhs){
                           return std::make_tuple(_lhs,_rhs);
                       }
            );

        std::make_heap(std::begin(data),std::end(data));

        REQUIRE( std::get<0>(data.front()) == Approx( 7.f ));

    }

    SECTION("make_heap gives same root as python example with tuple and custom comparator"){

        std::vector<std::tuple<float,int> >   data(nums.size());
        std::transform(std::begin(nums),std::end(nums),
                       std::begin(foo),
                       std::begin(data),
                       [](const float& _lhs, const int& _rhs){
                           return std::make_tuple(_lhs,_rhs);
                       }
            );

        auto comp = [](const std::tuple<float,int>& _lhs, const std::tuple<float,int>& _rhs){
            return std::get<0>(_lhs) < std::get<0>(_rhs);
        };
        std::make_heap(std::begin(data),std::end(data),comp);

        REQUIRE( std::get<0>(data.front()) == Approx( 7.f ));

    }



}


TEST_CASE_METHOD( image_fixture, "create heap from image", "[image]" ) {

    REQUIRE( data_.data() != nullptr );

    SECTION("default heap is not empty from input data"){

        auto q = ndtess::heap::build(data_.data(),shape);
        REQUIRE( ! q.empty() );

    }

    SECTION("compare outcome to python implementation with default map"){

        auto q = ndtess::heap::build(data_.data(),shape);

        REQUIRE( q.size() == 239 );

        auto i = q.top();

        REQUIRE( std::get<0>(i) == Approx ( 1.f ) );
        CHECK( std::get<1>(i) == 10 );
        CHECK( std::get<2>(i) == 0 );
        REQUIRE( std::get<3>(i) == Approx ( 100.f ) );

    }

    SECTION("compare outcome to python implementation with constant map"){

        auto q = ndtess::heap::build(data_.data(),shape, constant_map_.data());

        REQUIRE( q.size() == 239 );

        auto i = q.top();

        REQUIRE( std::get<1>(i) == 10 );
        REQUIRE( std::get<2>(i) == 0 );
        REQUIRE( std::get<3>(i) == Approx ( 100.f ) );

    }

    SECTION("compare outcome to python implementation with sinus map"){

        auto q = ndtess::heap::build(data_.data(),shape, constant_map_.data());

        REQUIRE( q.size() == 239 );

        auto i = q.top();

        REQUIRE( std::get<1>(i) == 10 );
        REQUIRE( std::get<2>(i) == 0 );
        REQUIRE( std::get<3>(i) == Approx ( 100.f ) );

    }

    SECTION("compare outcome to python implementation with random map"){

        auto q = ndtess::heap::build(data_.data(),shape, random_map_.data());

        REQUIRE( q.size() == 239 );

        auto i = q.top();

        // REQUIRE( std::get<1>(i) == 15 );
        // REQUIRE( std::get<2>(i) == 7 );
        REQUIRE( std::get<3>(i) == Approx ( 100.f ) );

    }
}
