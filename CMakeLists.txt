cmake_minimum_required(VERSION 2.6)
project(VISUALIZER)

#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
#find_package(GLUT)
#find_package(OpenGL)

SET (EXECUTABLE_OUTPUT_PATH
   ${PROJECT_BINARY_DIR}
   CACHE PATH
   "Single Directory for all Executables."
   )

# version number
SET(VERSION_MAJOR 1)
SET(VERSION_MINOR 4)
SET(VERSION_MICRO 4)
SET(VERSION_ADDITIONAL "rc1")

IF(VERSION_ADDITIONAL STREQUAL "")
    ADD_DEFINITIONS(-DVERSION_STRING="${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO}${VERSION_ADDITIONAL}")
ELSE()
    ADD_DEFINITIONS(-DVERSION_STRING="${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO}-${VERSION_ADDITIONAL}")
ENDIF()

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
add_subdirectory(src)
add_subdirectory(src/tests)
