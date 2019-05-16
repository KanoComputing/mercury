# Include python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

set(CMAKE_SWIG_FLAGS "-c++")
set_source_files_properties(../${PROJECT_NAME}.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Add swig module
message("HAW: ${PROJECT_NAME}")
swig_add_module(mercury python ../${PROJECT_NAME}.i)
#swig_link_libraries(mercury ${PROJECT_NAME} ${PYTHON_LIBRARIES})
swig_link_libraries(mercury ${PYTHON_LIBRARIES})
