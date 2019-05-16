project(mercury VERSION 0.1 LANGUAGES CXX)

add_library(mercury SHARED
    theme/theme.cpp
)

target_compile_options(mercury
    PRIVATE -fprofile-arcs -ftest-coverage
)

if(${CMAKE_VERSION} VERSION_LESS "3.10.0")
    set (CMAKE_LINKER_FLAGS "PRIVATE -coverage")
else()
    target_link_options(mercury
        PRIVATE -coverage
        )
endif()

target_include_directories(mercury PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

# Add swig subdirectory
add_subdirectory(swig)
