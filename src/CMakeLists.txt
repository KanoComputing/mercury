project(theme VERSION 0.1 LANGUAGES CXX)

add_library(mercury SHARED
    theme/theme.cpp
)

target_include_directories(mercury PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)
