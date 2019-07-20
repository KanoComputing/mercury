# Set up swig
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# Add subdirectories for each language if desired
option(BUILD_PYTHON "Build Python 3 SWIG module" ON)
option(BUILD_PYTHON2 "Build Python 2 SWIG module" ON)

if(BUILD_PYTHON)
  add_subdirectory(python3)
endif()

if(BUILD_PYTHON2)
  add_subdirectory(python2)
endif()
