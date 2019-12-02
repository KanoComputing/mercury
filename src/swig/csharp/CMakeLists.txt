#
#  CMake definition to generate Windows C# bindings
#

set(CSHARP_NAME ${PROJECT_NAME}_csharp)

message("SWIG PROJECT_NAME: ${CSHARP_NAME}")

set(CMAKE_SWIG_FLAGS "-csharp" "-addextern" "-Wall")

set_source_files_properties(../${PROJECT_NAME}.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Add swig module
if (${CMAKE_VERSION} VERSION_GREATER 3.8)
    swig_add_library(
        ${CSHARP_NAME}
        LANGUAGE csharp
        SOURCES ../${PROJECT_NAME}.i
    )
else()
    swig_add_module(${CSHARP_NAME} csharp ../${PROJECT_NAME}.i)
endif()

swig_link_libraries(${CSHARP_NAME} mercury_static)
