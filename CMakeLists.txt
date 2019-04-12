cmake_minimum_required(VERSION 3.7.2 FATAL_ERROR)
project(Mercury VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(src)

# FIXME: Find out how to accomodate the tests build on the PI,
# there are problems due to the CMake version.
#add_subdirectory(test)

enable_testing()
