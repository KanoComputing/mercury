
#
# FIXME: the find_package functions climbs up to loading python3,
#        cannot find a way around it - setting manual paths instead
# find_package(PythonLibs 2.7 EXACT REQUIRED)
#
set(PYTHON_INCLUDE_PATH "/usr/include/python2.7")
set(PYTHON_LIBRARIES "/usr/lib/arm-linux-gnueabihf/libpython2.7.so")

message("PYTHON2 include: ${PYTHON_INCLUDE_PATH}")
message("PYTHON2 libs: ${PYTHON_LIBRARIES}")

include_directories(${PYTHON_INCLUDE_PATH})

set(PYTHON2_NAME ${PROJECT_NAME}_python2)

message("SWIG PROJECT_NAME: ${PYTHON2_NAME}")

set(CMAKE_SWIG_FLAGS "-c++" "-addextern" "-Wall" "-builtin" "-modern")

set_source_files_properties(../${PROJECT_NAME}.i PROPERTIES CPLUSPLUS ON)
include_directories(..)

# Add swig module
if(${CMAKE_VERSION} VERSION_GREATER "3.8")
    swig_add_library(
        ${PYTHON2_NAME}
        LANGUAGE python
        SOURCES ../${PROJECT_NAME}.i
    )
else()
    swig_add_module(${PYTHON2_NAME} python ../${PROJECT_NAME}.i)
endif()

swig_link_libraries(${PYTHON2_NAME} mercury_shared ${PYTHON_LIBRARIES})
