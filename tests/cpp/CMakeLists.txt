# include_directories(.)
# include_directories(${PROJECT_SOURCE_DIR}/include)


add_library(catch_maino OBJECT catch_main.cpp)
target_compile_features(catch_maino PUBLIC cxx_std_14)
target_include_directories(catch_maino PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/> )

add_executable(test_cpp_add_scalar test_cpp_add_scalar.cpp $<TARGET_OBJECTS:catch_maino>)
target_compile_features(test_cpp_add_scalar PUBLIC cxx_std_14)
target_include_directories(test_cpp_add_scalar PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include > )

add_executable(test_heap_queue test_heap_queue.cpp $<TARGET_OBJECTS:catch_maino>)
target_compile_features(test_heap_queue PUBLIC cxx_std_14)
target_include_directories(test_heap_queue PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include > )
target_link_libraries(test_heap_queue PRIVATE pybind11::embed)

add_executable(test_vorimage_build test_vorimage_build.cpp $<TARGET_OBJECTS:catch_maino>)
target_compile_features(test_vorimage_build PUBLIC cxx_std_14)
target_include_directories(test_vorimage_build PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include > )
target_link_libraries(test_vorimage_build PRIVATE pybind11::embed)
