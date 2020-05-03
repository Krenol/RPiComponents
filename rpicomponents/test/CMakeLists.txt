# CMakeList.txt : CMake project for RPiComponents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.4)
set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard

project (rpicomponents_test_project)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(DOCTEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/doctest CACHE INTERNAL "Path to include folder for doctest")
 
set(TEST_PROJECT_SRCS 
${PROJECT_SOURCE_DIR}/test.cpp
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories(${DOCTEST_INCLUDE_DIR})

add_subdirectory (external/doctest)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${TEST_PROJECT_SRCS})



find_library(wiringPi REQUIRED)
find_library(wiringPiDev REQUIRED)
find_library(pthread REQUIRED)

target_link_libraries(${PROJECT_NAME} wiringPi)
target_link_libraries(${PROJECT_NAME} wiringPiDev)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} doctest)
target_link_libraries(${PROJECT_NAME} RPiComponents)