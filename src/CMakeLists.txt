project(mercury VERSION 0.1 LANGUAGES CXX)

# Compilation of sources into object

find_package(OpenSSL)

set(mercury_src
    http/http_client.cpp
    kes_dashboard_live_tiles_client/DefaultTileLoader.cpp
    kes_dashboard_live_tiles_client/OnlineLoader.cpp
    kes_dashboard_live_tiles_client/Tile.cpp
    kes_dashboard_live_tiles_client/TileCache.cpp
    kes_dashboard_live_tiles_client/TileFactory.cpp
    kes_dashboard_live_tiles_client/TileManager.cpp
    kes_moma_picks_client/DefaultPaintingLoader.cpp
    kes_moma_picks_client/OnlineLoader.cpp
    kes_moma_picks_client/Painting.cpp
    kes_moma_picks_client/PaintingCache.cpp
    kes_moma_picks_client/PaintingFactory.cpp
    kes_moma_picks_client/PaintingManager.cpp
    kw/APIConfig.cpp
    kw/kw.cpp
    theme/theme.cpp
    utils/Environment.cpp
    utils/Filesystem.cpp
    utils/String.cpp
    utils/Time.cpp
)

add_library(mercury_obj OBJECT
    ${mercury_src}
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
    PUBLIC CONAN_PKG::parson
           CONAN_PKG::Poco
           CONAN_PKG::yaml-cpp
           ${OPENSSL_LIBRARIES}
)
target_link_libraries(mercury_static
    PUBLIC CONAN_PKG::parson
           CONAN_PKG::Poco
           CONAN_PKG::yaml-cpp
           ${OPENSSL_LIBRARIES}
)


if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(mercury_obj
        PUBLIC -fsanitize=address,undefined
               -fno-omit-frame-pointer
               -fno-sanitize-recover=all
    )
    target_link_options(mercury_shared
        PUBLIC -fsanitize=address,undefined
               -fno-omit-frame-pointer
               -fno-sanitize-recover=all
    )
    target_link_options(mercury_static
        PUBLIC -fsanitize=address,undefined
               -fno-omit-frame-pointer
               -fno-sanitize-recover=all
    )

    # FIXME: Actually calculate whether the sanitizer is supported rather than
    #        relying on a static variable. This could be done with something
    #        like:
    #
    #            include(CheckCXXCompilerFlag)
    #            check_cxx_compiler_flag('-fsanitize=thread'
    #                                    THREAD_SANITIZER_SUPPORTED)
    #
    #        but was unable to get this to work properly
    #
    option(THREAD_SANITIZER_SUPPORTED
           "Whether the thread sanitizer is supported"
           OFF)

    if (THREAD_SANITIZER_SUPPORTED)
        add_library(mercury_thread_obj OBJECT
            ${mercury_src}
        )
        target_include_directories(mercury_thread_obj PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS}>
            $<INSTALL_INTERFACE:include>
        )
        set_property(TARGET mercury_thread_obj PROPERTY POSITION_INDEPENDENT_CODE ON)
        target_compile_options(mercury_thread_obj
            PUBLIC -fsanitize=thread,undefined
                -fno-omit-frame-pointer
                -fno-sanitize-recover=all
        )

        add_library(mercury_thread_static STATIC
            $<TARGET_OBJECTS:mercury_thread_obj>
        )
        set_target_properties(mercury_thread_static
            PROPERTIES OUTPUT_NAME mercury_thread
        )
        target_link_options(mercury_thread_static
            PUBLIC -fsanitize=thread,undefined
                -fno-omit-frame-pointer
                -fno-sanitize-recover=all
        )
        target_include_directories(mercury_thread_static PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CONAN_INCLUDE_DIRS}>
            $<INSTALL_INTERFACE:include>
        )
        target_link_libraries(mercury_thread_static
            PUBLIC CONAN_PKG::parson
                CONAN_PKG::Poco
                CONAN_PKG::yaml-cpp
                ${OPENSSL_LIBRARIES}
        )
    endif()

    # Add flags for coverage
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
endif (CMAKE_BUILD_TYPE MATCHES Debug)


# Add swig subdirectory
add_subdirectory(swig)
