cmake_minimum_required(VERSION 3.10)

project(bytecode_language LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #differernt compile options for different compilers
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-Wall -Wextra -g)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/W4 /DEBUG)
    else()
        message(WARNING "Unsupported compiler")
    endif()

    add_compile_definitions(_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    #differernt compile options for different compilers
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-O3)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/O2)
    else()
        message(WARNING "Unsupported compiler")
    endif()
endif()

file(GLOB_RECURSE BVM_SOURCES "src/bvm/*.cpp")
add_executable(bvm "src/bvm.cpp" ${BVM_SOURCES})

file(GLOB_RECURSE BCC_SOURCES "src/bcc/*.cpp")
add_executable(bcc "src/bcc.cpp" ${BCC_SOURCES})