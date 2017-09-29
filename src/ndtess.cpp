#include <iostream>
#include <pybind11/pybind11.h>

int add_scalars(int i, int j) {
	std::cout << "hey this is C++!\n";
    return i + j;
}

PYBIND11_MODULE(ndtess, m) {
    m.doc() = "simple function to add 2 scalars";

    m.def("add_scalars", &add_scalars, "A function which adds two numbers");
}
