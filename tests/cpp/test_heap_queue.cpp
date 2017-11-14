#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "catch.hpp"
#include "heapqueue.hpp"



struct image_fixture {

    std::vector<std::size_t> shape;
    const std::size_t len;
    std::vector<std::size_t> stride;
    std::vector<float> data_;


    image_fixture():
        shape({16,16}),
        len(16*16),
        stride({16*sizeof(float),sizeof(float)}),
        data_(16*16,0.f){

        for(std::size_t y = 0;y<shape[1];++y){
            for(std::size_t x = 0;x<shape[0];++x){
                if((x > 0 && x < 5) && (y > 10 && y < 15))
                    data_[y*shape[0] + x] = 42.f;

                std::size_t x_rel = x - 12;
                std::size_t y_rel = y - 4;
                if(((x_rel*x_rel) + (y_rel*y_rel)) < 16){
                    data_[y*shape[0] + x] = 100.f;
                }

#ifdef NDTESS_TRACE
                std::cout << std::setw(4) << data_[y*shape[0] + x] << " ";
#endif
            }

#ifdef NDTESS_TRACE
            std::cout << "\n";
#endif
        }

    }


};


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

    SECTION("compare outcome to python implementation"){

        auto q = ndtess::heap::build(data_.data(),shape);

        REQUIRE( q.size() == 239 );

        auto i = q.top();

        REQUIRE( std::get<0>(i) == Approx ( 1.f ) );
        CHECK( std::get<1>(i) == 10 );
        CHECK( std::get<2>(i) == 0 );
        REQUIRE( std::get<3>(i) == Approx ( 100.f ) );

    }
}
