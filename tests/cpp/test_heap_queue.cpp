#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

#include "catch.hpp"
#include "heapqueue.hpp"

// #include "pybind11/numpy.h"
// #include "pybind11/pybind11.h"


// namespace py = pybind11;

// static void setup_environment(){
//     try{
//         py::module::import("numpy");
//     } catch (...){
//         std::cerr << "urgs, unable to load numpy\n";
//     }
// }

struct image_fixture {

    std::vector<std::size_t> shape;
    const std::size_t len;
    std::vector<std::size_t> stride;
    std::vector<float> data_;
    // py::array_t<float,2>* image_;

    image_fixture():
        shape({32,32}),
        len(32*32),
        stride({32*sizeof(float),sizeof(float)}),
        data_(32*32,0.f){

        for(std::size_t y = 0;y<shape[1];++y){
            for(std::size_t x = 0;x<shape[1];++x){
                if((x > 5 && x < 11) && (y > 1 && y < 5))
                    data_[y*shape[0] + x] = 42.f;

                std::size_t x_rel = x - 24;
                std::size_t y_rel = y - 24;
                if(((x_rel*x_rel) + (y_rel*y_rel)) < 16)
                    data_[y*shape[0] + x] = 100.f;
            }
        }
        // py::capsule free_when_done(data_.data(), [](void *f) {
        //     float *foo = reinterpret_cast<float *>(f);
        //     delete[] foo;
        // });
        // setup_environment();
        // image_ = new py::array_t<float,2>();
        // // image_ = py::array_t<float,2>(shape,stride,data_.data(),free_when_done);

    }


};


TEST_CASE_METHOD( image_fixture, "fixture data correct", "[image]" ) {

    REQUIRE( data_.data() != nullptr );
    REQUIRE( data_[0] < 1.f );

    SECTION("small rectangle (x,y) = [6:11,2:5] was set"){
        REQUIRE( data_[3*shape[1]+8] != 0.f );
        REQUIRE( data_[3*shape[1]+8] == 42.f );
    }

    SECTION("small circle at (24,24) with radius 4"){
        REQUIRE( data_[24*shape[1]+24] != 0.f );
        REQUIRE( data_[24*shape[1]+24] == 100.f );
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

        REQUIRE( q.size() == 690 );

        auto i = q.front();

        REQUIRE( std::get<1>(i) == 5 );
        REQUIRE( std::get<2>(i) == 2 );

    }
}
