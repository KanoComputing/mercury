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
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)

target_link_options(mercury_gtests
    PRIVATE -Wl,-rpath,${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

if (UNIX AND NOT APPLE)
    target_link_options(mercury_gtests
        PRIVATE -static-libasan
    )
endif ()

enable_testing()
gtest_discover_tests(mercury_gtests)

# Thread tests

if (THREAD_SANITIZER_SUPPORTED)
    add_executable(mercury_thread_tests
        thread_tests.cpp
    )

    target_link_libraries(mercury_thread_tests
        PUBLIC mercury_thread_static
        PRIVATE CONAN_PKG::gtest
    )

    target_include_directories(mercury_thread_tests PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        ${CMAKE_SOURCE_DIR}/include
    )

    target_link_options(mercury_thread_tests
        PRIVATE -Wl,-rpath,${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    )
endif()

# Coverage code test
# NOTE: not supported yet on Windows platforms
if (NOT WIN32)
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_LCOV_EXCLUDES
        '*/build/*' '*/test/*' '*/.conan/*' '*v1/*' '/usr/include/*'
    )
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage
        EXECUTABLE ctest -j ${n_cores} --no-compress-output -T test
        ENVIRONMENT LSAN_OPTIONS=verbosity=1:log_threads=1
        DEPENDENCIES
        mercury_obj
        mercury_static
        mercury_shared
        mercury_gtests
    )
endif()

# FIXME: Poco library is still giving us obscure linking troubles
# the code below does not fix the linking stage yet
if(MSVC)
  set(CMAKE_STATIC_LINKER_FLAGS
      "${CMAKE_STATIC_LINKER_FLAGS}
      /NODEFAULTLIB:\"PocoFoundation.lib\"
      /NODEFAULTLIB:\"PocoNet.lib\"
      /NODEFAULTLIB:\"PocoNetSSLWin.lib\"
      /NODEFAULTLIB:\"PocoUtil.lib\""
  )
endif()
