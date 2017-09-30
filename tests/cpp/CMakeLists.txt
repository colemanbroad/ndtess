include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test_cpp_add_scalar test_cpp_add_scalar.cpp)
target_compile_features(test_cpp_add_scalar PUBLIC cxx_auto_type)
