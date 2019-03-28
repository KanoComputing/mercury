cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(Mercury VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(src)
