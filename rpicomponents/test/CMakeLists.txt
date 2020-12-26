# CMakeList.txt : CMake project for RPiComponents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.4)
set(CMAKE_CXX_STANDARD 14)  # enable C++14 standard

project (rpicomponents_test_project)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(TEST_PROJECT_SRCS 
${PROJECT_SOURCE_DIR}/test.cpp
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories(${DOCTEST_INCLUDE_DIR})


# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${TEST_PROJECT_SRCS})



find_library(pigpio REQUIRED)
find_library(pthread REQUIRED)
find_library(nlohmann_json::nlohmann_json REQUIRED)
find_library(atomic REQUIRED)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} utils)
target_link_libraries(${PROJECT_NAME} rpicomponents)
target_link_libraries(${PROJECT_NAME} rpipins)
target_link_libraries(${PROJECT_NAME} pigpio)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} atomic)