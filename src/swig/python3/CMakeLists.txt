# Include python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})

set(PYTHON3_NAME ${PROJECT_NAME}_python3)

message("SWIG PROJECT_NAME: ${PYTHON3_NAME}")

set(CMAKE_SWIG_FLAGS "-c++" "-addextern" "-Wall" "-py3" "-builtin" "-modern")

set_source_files_properties(../${PROJECT_NAME}.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Add swig module
if(${CMAKE_VERSION} VERSION_GREATER "3.8")
    swig_add_library(
        ${PYTHON3_NAME}
        LANGUAGE python
        SOURCES ../${PROJECT_NAME}.i
    )
else()
    swig_add_module(${PYTHON3_NAME} python ../${PROJECT_NAME}.i)
endif()

swig_link_libraries(${PYTHON3_NAME} mercury_shared ${PYTHON_LIBRARIES})
