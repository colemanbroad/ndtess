#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>

#include "catch.hpp"
#include "detail/heapqueue.hpp"
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


    SECTION("from-zeroes"){

        auto q = ndtess::heap::build(data_.data(),shape);

        REQUIRE( q.size() == 239 );

        const std::vector<ndtess::item<float> > expected = {
            std::make_tuple(1.f,  0, 11,  42.f),
            std::make_tuple(1.f,  1, 10,  42.f),
            std::make_tuple(1.f,  0, 12,  42.f),
            std::make_tuple(1.f,  8,  6, 100.f),
            std::make_tuple(1.f,  1, 11,  42.f),
            std::make_tuple(1.f,  0, 13,  42.f),
            std::make_tuple(1.f,  0, 14,  42.f),
            std::make_tuple(1.f,  9,  1, 100.f),
            std::make_tuple(1.f,  9,  3, 100.f),
            std::make_tuple(1.f,  9,  4, 100.f),
            std::make_tuple(1.f,  1, 12,  42.f),
            std::make_tuple(1.f,  1, 12,  42.f),
            std::make_tuple(1.f,  1, 11,  42.f),
            std::make_tuple(1.f,  1, 13,  42.f),
            std::make_tuple(1.f, 10,  2, 100.f),
            std::make_tuple(1.f,  9,  5, 100.f)
        };


        for( int i = 0;i < expected.size() ;++i){
            auto t = q.top();
            auto e = expected[i];
            INFO("item-from-zeroes :: " << i);
            REQUIRE( std::get<0>(t) == Approx ( std::get<0>(e) ) );
            CHECK  ( std::get<1>(t) == std::get<1>(e) );
            CHECK  ( std::get<2>(t) == std::get<2>(e)  );
            REQUIRE( std::get<3>(t) == Approx (  std::get<3>(e) ) );
            q.pop();
        }
    }

    SECTION("default-heap-not-empty"){

        auto q = ndtess::heap::build(data_.data(),shape);
        REQUIRE( ! q.empty() );

    }


    SECTION("from-constant"){

        auto q = ndtess::heap::build(data_.data(),shape, constant_map_.data());

        REQUIRE( q.size() == 239 );

        auto i = q.top();

        REQUIRE( std::get<1>(i) == 10 );
        REQUIRE( std::get<2>(i) == 0 );
        REQUIRE( std::get<3>(i) == Approx ( 100.f ) );

    }

    SECTION("from-sinus"){

        auto q = ndtess::heap::build(data_.data(),shape, constant_map_.data());

        REQUIRE( q.size() == 239 );

        auto i = q.top();

        REQUIRE( std::get<1>(i) == 10 );
        REQUIRE( std::get<2>(i) == 0 );
        REQUIRE( std::get<3>(i) == Approx ( 100.f ) );

    }

    SECTION("from-noise"){

        auto q = ndtess::heap::build(data_.data(),shape, random_map_.data());

        REQUIRE( q.size() == 239 );

        auto i = q.top();

        // REQUIRE( std::get<1>(i) == 15 );
        // REQUIRE( std::get<2>(i) == 7 );
        REQUIRE( std::get<3>(i) == Approx ( 100.f ) );

    }
}
