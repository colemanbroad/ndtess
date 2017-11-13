#include <vector>
#include <cstdint>
#include <iostream>

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

    REQUIRE( data_[3*shape[1]+8] != 0.f );
    REQUIRE( data_[3*shape[1]+8] == 42.f );

    REQUIRE( data_[24*shape[1]+24] != 0.f );
    REQUIRE( data_[24*shape[1]+24] == 100.f );


}
