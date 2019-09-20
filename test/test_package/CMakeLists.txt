cmake_minimum_required(VERSION 2.8.12)
project(PackageTest CXX)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(example example.cpp)

target_include_directories(example PUBLIC
    ${CONAN_INCLUDE_DIRS}>
)

target_link_libraries(example
    PUBLIC CONAN_PKG::Mercury
)
