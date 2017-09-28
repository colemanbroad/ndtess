include_directories(.)

add_executable(first first.cpp)
target_compile_features(first PRIVATE cxx_auto_type)
