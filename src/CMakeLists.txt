project(theme VERSION 0.1 LANGUAGES CXX)

add_library(mercury SHARED
    theme/theme.cpp
)

target_compile_options(mercury
	PRIVATE -fprofile-arcs -ftest-coverage
)

# option below is available starting with cmake 3.13
# cmake on the pi is v3.7.2
#target_link_options(mercury
#	PRIVATE -coverage
#)

target_include_directories(mercury PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)
