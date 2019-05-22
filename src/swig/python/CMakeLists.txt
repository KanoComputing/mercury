# Include python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

message("SWIG PROJECT_NAME: ${PROJECT_NAME}")

set(CMAKE_SWIG_FLAGS "-c++" "-addextern" "-Wall" "-py3" "-builtin" "-modern")

set_source_files_properties(../${PROJECT_NAME}.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Add swig module
swig_add_module(mercury python ../${PROJECT_NAME}.i)
swig_link_libraries(mercury ${PROJECT_NAME} ${PYTHON_LIBRARIES})
