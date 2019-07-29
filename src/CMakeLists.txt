project(mercury VERSION 0.1 LANGUAGES CXX)

# Compilation of sources into object

find_package(OpenSSL)

add_library(mercury_obj OBJECT
    _http/http_client.cpp
    kes_dashboard_live_tiles_cli/DefaultTileLoader.cpp
    kes_dashboard_live_tiles_cli/OnlineLoader.cpp
    kes_dashboard_live_tiles_cli/Tile.cpp
    kes_dashboard_live_tiles_cli/TileCache.cpp
    kes_dashboard_live_tiles_cli/TileFactory.cpp
    kes_dashboard_live_tiles_cli/TileManager.cpp
    kw/kw.cpp
    theme/theme.cpp
    utils/Filesystem.cpp
    utils/String.cpp
    utils/Time.cpp
)
target_include_directories(mercury_obj PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
)
set_property(TARGET mercury_obj PROPERTY POSITION_INDEPENDENT_CODE ON)

# Create static and shared libraries

add_library(mercury_shared SHARED $<TARGET_OBJECTS:mercury_obj>)
add_library(mercury_static STATIC $<TARGET_OBJECTS:mercury_obj>)

set_target_properties(mercury_shared
    PROPERTIES OUTPUT_NAME mercury
)
set_target_properties(mercury_static
    PROPERTIES OUTPUT_NAME mercury
)
set_property(TARGET mercury_static PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(mercury_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
)
target_include_directories(mercury_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(mercury_shared
    PUBLIC CONAN_PKG::parson CONAN_PKG::Poco ${OPENSSL_LIBRARIES}
)
target_link_libraries(mercury_static
    PUBLIC CONAN_PKG::parson CONAN_PKG::Poco ${OPENSSL_LIBRARIES}
)


if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(mercury_obj
        PRIVATE -fsanitize=address,undefined -fno-sanitize-recover=all
    )
    target_link_options(mercury_shared
        PRIVATE -fsanitize=address,undefined -fno-sanitize-recover=all
    )
    target_link_options(mercury_static
        PRIVATE -fsanitize=address,undefined -fno-sanitize-recover=all
    )

    # Add flags for coverage
    # TODO: Only do this if we are building the debug version
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
endif (CMAKE_BUILD_TYPE MATCHES Debug)


# Add swig subdirectory
add_subdirectory(swig)
