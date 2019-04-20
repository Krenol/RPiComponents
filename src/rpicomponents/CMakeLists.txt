# CMakeList.txt : CMake project for RPiComponents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

SET(TARGET_H
    component/component.hpp
    pin/pin.hpp)

# Local source files here
SET(TARGET_SRC
    pin/pin.cpp
	component/component.cpp)

# Add source to this project's executable.
add_executable (RPiComponents "rpicomponents.cpp" "rpicomponents.hpp" ${TARGET_H} ${TARGET_SRC})

# TODO: Add tests and install targets if needed.
add_subdirectory ("component")
add_subdirectory ("pin")

target_link_libraries(${PROJECT_NAME} wiringPi)
target_link_libraries(${PROJECT_NAME} wiringPiDev)
target_link_libraries(${PROJECT_NAME} pthread)