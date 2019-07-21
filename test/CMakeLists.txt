if(${CMAKE_VERSION} VERSION_LESS "3.10.0")
    message(FATAL_ERROR "ERROR: You need CMake version 3.10.0 or above in order to run tests")
endif()

find_package(GTest)
include(GoogleTest)
add_executable(mercury_gtests
    test.cpp
)

target_link_libraries(mercury_gtests
    PUBLIC mercury_static
    PRIVATE CONAN_PKG::gtest
)

target_include_directories(mercury_gtests PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../..>
)

target_link_options(mercury_gtests
    PRIVATE -fsanitize=address,undefined
            -fno-sanitize-recover=all
            -Wl,-rpath,${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

if (UNIX AND NOT APPLE)
    target_link_options(mercury_gtests
        PRIVATE -static-libasan
    )
endif ()

enable_testing()
gtest_discover_tests(mercury_gtests)

# Coverage
include(CodeCoverage)
APPEND_COVERAGE_COMPILER_FLAGS()
set(COVERAGE_LCOV_EXCLUDES
    '*/build/*' '*/test/*' '*/.conan/*' '*v1/*'
)
SETUP_TARGET_FOR_COVERAGE_LCOV(
    NAME coverage
    EXECUTABLE ctest -j ${n_cores}
    ENVIRONMENT LSAN_OPTIONS=verbosity=1:log_threads=1
    DEPENDENCIES
    mercury_obj
    mercury_static
    mercury_shared
    mercury_gtests
)
