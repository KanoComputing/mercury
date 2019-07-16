# Include python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

message("SWIG PROJECT_NAME: ${PROJECT_NAME}")

set(CMAKE_SWIG_FLAGS "-c++" "-addextern" "-Wall" "-py3" "-builtin" "-modern")

set_source_files_properties(../${PROJECT_NAME}.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Add swig module
if(${CMAKE_VERSION} VERSION_GREATER "3.7")
swig_add_library(
    mercury
    LANGUAGE python
    SOURCES ../${PROJECT_NAME}.i
    )
else()
  swig_add_module (mercury python ../${PROJECT_NAME}.i)
endif()

swig_link_libraries(mercury mercury_shared ${PYTHON_LIBRARIES})
