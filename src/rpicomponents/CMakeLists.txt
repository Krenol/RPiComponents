# CMakeList.txt : CMake project for RPiComponents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.4)

SET(TARGET_H
    component/component.hpp
    pin/pinchecker.hpp
	pin/pin.hpp
	pin/digitalpin.hpp
	pin/softpwmpin.hpp
	pin/pwmpin.hpp
	pin/softtonepin.hpp
	pin/pinfactory.hpp
	pin/inputpin.hpp
	component/led.hpp
	component/button.hpp)

# Local source files here
SET(TARGET_SRC
    pin/pinchecker.cpp
	pin/pin.cpp
	pin/digitalpin.cpp
	pin/softpwmpin.cpp
	pin/pwmpin.cpp
	pin/softtonepin.cpp
	pin/pinfactory.cpp
	pin/inputpin.cpp
	component/component.cpp
	component/led.cpp
	component/button.cpp)

# Add source to this project's executable.
add_executable (RPiComponents "test.cpp" "rpicomponents.hpp" ${TARGET_H} ${TARGET_SRC})

target_link_libraries(${PROJECT_NAME} wiringPi)
target_link_libraries(${PROJECT_NAME} wiringPiDev)
target_link_libraries(${PROJECT_NAME} pthread)