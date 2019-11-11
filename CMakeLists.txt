#
# Main CMake file
#

# Minimum CMake version required to build the software
cmake_minimum_required(VERSION 3.7.2 FATAL_ERROR)

set(CMAKE_VERBOSE_MAKEFILE on)

project(Mercury VERSION 0.1)

# Add cmake directory to include path. These are shared modules from
#     https://github.com/bilke/cmake-modules
# See the README there for instructions to update
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(UseBackportedModules)

# Global settings
set(CMAKE_CXX_STANDARD 14)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Inject CMake variables for C++ to use
configure_file(
    ${CMAKE_SOURCE_DIR}/include/mercury/config.h.in
    ${CMAKE_SOURCE_DIR}/include/mercury/config.h
)

# Add subdirectories

add_subdirectory(src)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (${CMAKE_VERSION} VERSION_GREATER "3.10.0")
        add_subdirectory(test)
    endif ()
endif (CMAKE_BUILD_TYPE MATCHES Debug)

# For some reason this is mandatory on Windows, or above if() fails
if (WIN32)
    add_subdirectory(test)
    add_test(NAME mercury_tests COMMAND mercury_gtest)
endif()

enable_testing()
