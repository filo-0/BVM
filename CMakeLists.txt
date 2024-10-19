cmake_minimum_required(VERSION 3.5)

project(bytecode_language LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -Wall -Wextra)
    add_compile_definitions(_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
endif()

file(GLOB_RECURSE BVM_SOURCES "src/bvm/*.cpp")
add_executable(bvm "src/bvm.cpp" ${BVM_SOURCES})

file(GLOB_RECURSE BCC_SOURCES "src/bcc/*.cpp")
add_executable(bcc src/bcc.cpp ${BVM_SOURCES} ${BCC_SOURCES})