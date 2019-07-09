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
${PROJECT_SOURCE_DIR}/transistor.cpp
${PROJECT_SOURCE_DIR}/ultrasonicsensor.cpp
${PROJECT_SOURCE_DIR}/dht11.cpp
${PROJECT_SOURCE_DIR}/pcf8574.cpp
${PROJECT_SOURCE_DIR}/pcf8591.cpp
${PROJECT_SOURCE_DIR}/pcf.cpp
${PROJECT_SOURCE_DIR}/mpu6050.cpp
${PROJECT_SOURCE_DIR}/q74hc595.cpp
${PROJECT_SOURCE_DIR}/motionsensor.cpp
${PROJECT_SOURCE_DIR}/photoresistor.cpp
)
 
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_library(${PROJECT_NAME} SHARED ${RPICOMPONENT_PROJECT_SRCS})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

add_subdirectory (pin)
add_subdirectory (test)
add_subdirectory (utils)
target_link_libraries(${PROJECT_NAME} pin)
target_link_libraries(${PROJECT_NAME} rpicomponents_utils)