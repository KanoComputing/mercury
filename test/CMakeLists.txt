if(${CMAKE_VERSION} VERSION_LESS "3.10.0")

  message("WARNING: You need CMake version 3.10.0 or above in order to run tests")

else()

    find_package(GTest)
    include(GoogleTest)
    add_executable(mercury_gtests
      test.cpp
      )

    target_link_libraries(mercury_gtests
      PUBLIC mercury
      PRIVATE GTest::Main GTest::GTest CONAN_PKG::gtest
      )

    target_compile_options(mercury_gtests
      PRIVATE -fprofile-arcs -ftest-coverage
      )

    target_link_options(mercury_gtests
      PRIVATE -coverage -Wl,-rpath,${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
      )

    enable_testing()
    gtest_discover_tests(mercury_gtests)

endif()
