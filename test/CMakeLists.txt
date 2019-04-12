find_package(GTest)
include(GoogleTest)


add_executable(mercury_gtests
    test.cpp
)

target_link_libraries(mercury_gtests
    PUBLIC mercury
    PRIVATE GTest::GTest GTest::Main CONAN_PKG::gtest
)

target_compile_options(mercury_gtests
    PRIVATE -fprofile-arcs -ftest-coverage
)

# again, option not available on cmake version on the pi
target_link_options(mercury_gtests
    PRIVATE -coverage -rpath ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)


enable_testing()
gtest_discover_tests(mercury_gtests)
