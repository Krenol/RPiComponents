# CMakeList.txt : CMake project for RPiComponents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.4)

project (i2cdevlib)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/i2cdevlib)


 
set(I2C_PROJECT_SRCS 
${PROJECT_SOURCE_DIR}/Arduino/MPU6050/MPU6050.cpp
${PROJECT_SOURCE_DIR}/RaspberryPi_bcm2835/I2Cdev/I2Cdev.cpp
)

 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories( "i2cdevlib/RaspberryPi_bcm2835/I2Cdev" )

 
add_library(${PROJECT_NAME} SHARED ${I2C_PROJECT_SRCS})

find_library(bcm2835 REQUIRED)

target_link_libraries(${PROJECT_NAME} bcm2835)


target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)
