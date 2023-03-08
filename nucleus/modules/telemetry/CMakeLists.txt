cmake_minimum_required(VERSION 2.8)
project(onboardsdk-custom-telemetry)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -O0")

FILE(GLOB SOURCE_FILES *.hpp *.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../common/dji_linux_environment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../common/dji_linux_helpers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../hal/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../osal/*.c
        )

if (OSDK_HOTPLUG)
    FILE(GLOB SOURCE_FILES ${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/../hal/hotplug/*.c)
endif ()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})