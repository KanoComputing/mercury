project(mercury VERSION 0.1 LANGUAGES CXX)

# Compilation of sources into object

add_library(mercury_obj OBJECT
    theme/theme.cpp
    kw/kw.cpp
)
target_include_directories(mercury_obj PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBCURL}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_PARSON}>
    $<INSTALL_INTERFACE:include>
)

# Create static and shared libraries

add_library(mercury_shared SHARED $<TARGET_OBJECTS:mercury_obj>)
add_library(mercury_static STATIC $<TARGET_OBJECTS:mercury_obj>)

set_target_properties(mercury_shared
    PROPERTIES OUTPUT_NAME mercury
)
set_target_properties(mercury_static
    PROPERTIES OUTPUT_NAME mercury
)

find_package(gcov)

target_link_libraries(mercury_shared
    PUBLIC ${GCOV_LIBRARIES}
)
target_link_libraries(mercury_static
    PUBLIC ${GCOV_LIBRARIES}
)

if(${CMAKE_VERSION} VERSION_LESS "3.10.0")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -coverage")
else()
    target_link_options(mercury_shared
        PRIVATE -coverage
    )
    target_link_options(mercury_static
        PRIVATE -coverage
    )
endif()

target_include_directories(mercury_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBCURL}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_PARSON}>
    $<INSTALL_INTERFACE:include>
)
target_include_directories(mercury_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBCURL}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_PARSON}>
    $<INSTALL_INTERFACE:include>
    )

target_link_libraries(mercury_shared
    PUBLIC CONAN_PKG::libcurl CONAN_PKG::parson
)
target_link_libraries(mercury_static
    PUBLIC CONAN_PKG::libcurl CONAN_PKG::parson
)

# Add swig subdirectory
add_subdirectory(swig)
