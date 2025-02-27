cmake_minimum_required(VERSION 3.19.2)
set(CMAKE_CXX_STANDARD 20)
project(Beta)

add_compile_definitions(BYTECODES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/bytecodes")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #differernt compile options for different compilers
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror -g)
        add_compile_definitions(_GNU)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror -g)
        add_compile_definitions(_CLANG)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/W4 /WX /DEBUG)
        add_compile_definitions(_MSVC)
    else()
        message(WARNING "Unsupported compiler")
    endif()
    add_compile_definitions(_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    #differernt compile options for different compilers
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_definitions(_GNU)
        add_compile_options(-O3)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_definitions(_CLANG)
        add_compile_options(-O3)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_definitions(_MSVC)
        add_compile_options(/O2)
    else()
        message(WARNING "Unsupported compiler")
    endif()
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8) #!64bit
    message(ERROR "Does not support 32bit systems")
endif()

include_directories(include)

file(GLOB_RECURSE BVM_SOURCES "src/bvm/*.cpp")
add_executable(bvm "src/bvm.cpp" ${BVM_SOURCES})

#target_precompile_headers(bvm PRIVATE "include/std.hpp")

file(GLOB_RECURSE BCC_SOURCES "src/bcc/*.cpp")
add_executable(bcc "src/bcc.cpp" ${BCC_SOURCES})

#target_precompile_headers(bcc REUSE_FROM bvm)