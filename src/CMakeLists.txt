project(theme VERSION 0.1 LANGUAGES CXX)

add_library(mercury SHARED
    theme/theme.cpp
)

target_compile_options(mercury
	PRIVATE -fprofile-arcs -ftest-coverage
)
target_link_options(mercury
	PRIVATE -coverage
)

target_include_directories(mercury PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)
