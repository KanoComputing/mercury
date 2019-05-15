#
# Main CMake file
#

# Minimum CMake version required to build the software
cmake_minimum_required(VERSION 3.7.2 FATAL_ERROR)

project(Mercury VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(src)

if(${CMAKE_VERSION} VERSION_GREATER "3.10.0")
    add_subdirectory(test)
endif()

enable_testing()
