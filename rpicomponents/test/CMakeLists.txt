# CMakeList.txt : CMake project for RPiComponents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.4)

project (test_project)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(TEST_PROJECT_SRCS 
${PROJECT_SOURCE_DIR}/test.cpp
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

# Add source to this project's executable.
add_executable (test_project ${TEST_PROJECT_SRCS})

target_link_libraries(test_project RPiComponents)

find_library(wiringPi REQUIRED)
find_library(wiringPiDev REQUIRED)
find_library(pthread REQUIRED)

target_link_libraries(${PROJECT_NAME} wiringPi)
target_link_libraries(${PROJECT_NAME} wiringPiDev)
target_link_libraries(${PROJECT_NAME} pthread)