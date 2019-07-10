project(mercury VERSION 0.1 LANGUAGES CXX)

add_library(mercury SHARED
    theme/theme.cpp
    kw/kw.cpp
)

target_compile_options(mercury
    PRIVATE -fprofile-arcs -ftest-coverage
)

if(${CMAKE_VERSION} VERSION_LESS "3.10.0")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -coverage -lgcov")
else()
    target_link_options(mercury
        PRIVATE -coverage -lgcov
        )
endif()

target_include_directories(mercury PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBCURL}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_PARSON}>
    $<INSTALL_INTERFACE:include>
    )

target_link_libraries(mercury CONAN_PKG::libcurl CONAN_PKG::parson)

# Add swig subdirectory
add_subdirectory(swig)
