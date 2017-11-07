include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/include)



add_library(catch_maino OBJECT catch_main.cpp)

add_executable(test_cpp_add_scalar test_cpp_add_scalar.cpp $<TARGET_OBJECTS:catch_maino>)
target_compile_features(test_cpp_add_scalar PUBLIC cxx_auto_type)


add_executable(test_heap_queue test_heap_queue.cpp $<TARGET_OBJECTS:catch_maino>)
target_compile_features(test_heap_queue PUBLIC cxx_auto_type)
target_link_libraries(test_heap_queue PRIVATE pybind11::embed)
