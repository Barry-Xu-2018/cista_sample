cmake_minimum_required(VERSION 3.8)

project(img_ser_deser LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(img_ser_deser src/img_ser_deser.cpp)
target_include_directories(img_ser_deser PRIVATE third_part/cista/include)
