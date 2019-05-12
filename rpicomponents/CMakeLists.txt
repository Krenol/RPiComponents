# CMakeList.txt : CMake project for RPiComponents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.4)
set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard

project (RPiComponents VERSION 1.0.0)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(RPICOMPONENT_PROJECT_SRCS 
${PROJECT_SOURCE_DIR}/button.cpp
${PROJECT_SOURCE_DIR}/component.cpp
${PROJECT_SOURCE_DIR}/led.cpp
)
 
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_library(${PROJECT_NAME} SHARED ${RPICOMPONENT_PROJECT_SRCS})


add_subdirectory (pin)
add_subdirectory (test)