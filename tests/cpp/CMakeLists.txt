include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(catch_maino OBJECT catch_main.cpp)
target_compile_features(catch_maino PUBLIC cxx_std_14)

add_executable(test_cpp_add_scalar test_cpp_add_scalar.cpp $<TARGET_OBJECTS:catch_maino>)
target_compile_features(test_cpp_add_scalar PUBLIC cxx_std_14)

add_executable(test_heap_queue test_heap_queue.cpp $<TARGET_OBJECTS:catch_maino>)
target_compile_features(test_heap_queue PUBLIC cxx_std_14)
target_link_libraries(test_heap_queue PRIVATE pybind11::embed)
