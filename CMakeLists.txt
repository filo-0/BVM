cmake_minimum_required(VERSION 3.5)

project(bvm LANGUAGES CXX)

include_directories(include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -Wall -Wextra)
    add_compile_definitions(_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
endif()

add_executable(bvm src/main.cpp src/bvm.cpp)