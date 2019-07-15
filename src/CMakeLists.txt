project(mercury VERSION 0.1 LANGUAGES CXX)

# Compilation of sources into object

find_package(OpenSSL)

add_library(mercury_obj OBJECT
    theme/theme.cpp
    kw/kw.cpp
    _http/http_client.cpp
)
target_include_directories(mercury_obj PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBCURL}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_PARSON}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_POCO}>
    ${OPENSSL_INCLUDE_DIR}
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

target_include_directories(mercury_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBCURL}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_PARSON}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_POCO}>
    ${OPENSSL_INCLUDE_DIR}
    $<INSTALL_INTERFACE:include>
)
target_include_directories(mercury_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_LIBCURL}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_PARSON}>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS_POCO}>
    ${OPENSSL_INCLUDE_DIR}
    $<INSTALL_INTERFACE:include>
    )

target_link_libraries(mercury_shared
    PUBLIC CONAN_PKG::libcurl CONAN_PKG::parson CONAN_PKG::Poco ${OPENSSL_LIBRARIES}
)
target_link_libraries(mercury_static
    PUBLIC CONAN_PKG::libcurl CONAN_PKG::parson CONAN_PKG::Poco ${OPENSSL_LIBRARIES}
)

# Add swig subdirectory
add_subdirectory(swig)
