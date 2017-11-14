#ifndef FIXTURES_H
#define FIXTURES_H

#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cmath>

struct image_fixture {

    std::vector<std::size_t> shape;
    static constexpr std::size_t len = 16*16;
    std::vector<std::size_t> stride;
    std::vector<float> data_;

    std::vector<float> constant_map_;
    std::vector<float> sinus_map_;
    std::vector<float> random_map_;

    image_fixture():
        shape({16,16}),
        stride({16*sizeof(float),sizeof(float)}),
        data_(len,0.f),
        constant_map_(len,3.3f),
        sinus_map_(len,0.f),
        random_map_(len,0.f)
        {

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

        std::size_t count = 0;
        for(float& el : sinus_map_){
            float x = float(count) / sinus_map_.size();
                el = std::sin(x) + 0.1;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        gen.seed(1307);

        std::uniform_real_distribution<> d(0.,1.);
        std::generate(std::begin(random_map_),std::end(random_map_),[&]( ){ return 3.3*d(gen);});

    }


};


#endif /* FIXTURES_H */
