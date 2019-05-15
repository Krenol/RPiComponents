# CMakeList.txt : CMake project for RPiComponents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.4)

project (pins)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(PIN_PROJECT_SRCS 
${PROJECT_SOURCE_DIR}/pinchecker.cpp
${PROJECT_SOURCE_DIR}/pin.cpp
${PROJECT_SOURCE_DIR}/digitalpin.cpp
${PROJECT_SOURCE_DIR}/softpwmpin.cpp
${PROJECT_SOURCE_DIR}/pwmpin.cpp
${PROJECT_SOURCE_DIR}/softtonepin.cpp
${PROJECT_SOURCE_DIR}/pinfactory.cpp
${PROJECT_SOURCE_DIR}/inputpin.cpp
)

 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
 
add_library(${PROJECT_NAME} SHARED ${PIN_PROJECT_SRCS})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)

# Locate libraries and headers
find_package(Threads REQUIRED)
