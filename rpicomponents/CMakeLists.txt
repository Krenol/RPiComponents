project (rpicomponents VERSION 1.0.0)

 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)


set(RPICOMPONENT_PROJECT_SRCS 
${PROJECT_SOURCE_DIR}/I2Cdev/I2Cdev.cpp
${PROJECT_SOURCE_DIR}/inv_mpu_lib/inv_mpu_dmp_motion_driver.c
${PROJECT_SOURCE_DIR}/inv_mpu_lib/inv_mpu.c
${PROJECT_SOURCE_DIR}/button.cpp
${PROJECT_SOURCE_DIR}/component.cpp
${PROJECT_SOURCE_DIR}/led.cpp
${PROJECT_SOURCE_DIR}/transistor.cpp
${PROJECT_SOURCE_DIR}/ultrasonicsensor.cpp
${PROJECT_SOURCE_DIR}/dht11.cpp
${PROJECT_SOURCE_DIR}/pcf8574.cpp
${PROJECT_SOURCE_DIR}/pcf8591.cpp
${PROJECT_SOURCE_DIR}/pcf.cpp
${PROJECT_SOURCE_DIR}/sensor.cpp
${PROJECT_SOURCE_DIR}/q74hc595.cpp
${PROJECT_SOURCE_DIR}/motionsensor.cpp
${PROJECT_SOURCE_DIR}/photoresistor.cpp
${PROJECT_SOURCE_DIR}/l293d.cpp
${PROJECT_SOURCE_DIR}/joystick.cpp
${PROJECT_SOURCE_DIR}/key.cpp
${PROJECT_SOURCE_DIR}/keypad.cpp
${PROJECT_SOURCE_DIR}/lcd.cpp
${PROJECT_SOURCE_DIR}/lcd1602.cpp
${PROJECT_SOURCE_DIR}/motor.cpp
${PROJECT_SOURCE_DIR}/steppermotor.cpp
${PROJECT_SOURCE_DIR}/bidirectionalmotor.cpp
${PROJECT_SOURCE_DIR}/undirectionalmotor.cpp
${PROJECT_SOURCE_DIR}/esc.cpp
${PROJECT_SOURCE_DIR}/servomotor.cpp
${PROJECT_SOURCE_DIR}/wiringSerial.c
${PROJECT_SOURCE_DIR}/gps_neo6mv2.cpp
${PROJECT_SOURCE_DIR}/bmp180.cpp
${PROJECT_SOURCE_DIR}/ahrs.cpp
)

add_library(${PROJECT_NAME} SHARED ${RPICOMPONENT_PROJECT_SRCS})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
    PRIVATE
        ${PROJECT_SOURCE_DIR}
)
if (NOT TARGET rpipins)
    add_subdirectory (external/RPiPins)
endif ()
if (NOT TARGET utils)
    add_subdirectory (external/CppUtils)
endif ()
if (NOT TARGET nlohmann_json::nlohmann_json)
    set(JSON_BuildTests OFF CACHE INTERNAL "")
    set(JSON_Install OFF CACHE INTERNAL "")
    add_subdirectory (external/json)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE atomic)
target_link_libraries(${PROJECT_NAME} PUBLIC rpipins)
target_link_libraries(${PROJECT_NAME} PRIVATE utils)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_compile_definitions(${PROJECT_NAME} PRIVATE MPU6050)
if(${BUILD_TEST})
    add_subdirectory(test)
endif()