cmake_minimum_required(VERSION 2.8)
project(onboardsdk)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(DJIOSDK 0)
set(DJIOSDK_MINOR_VERSION 1)
set(DJIOSDK_PATCH_VERSION 0)
set(DJIOSDK_VERSION
  ${DJIOSDK_MAJOR_VERSION}.${DJIOSDK_MINOR_VERSION}.${DJIOSDK_PATCH_VERSION})

add_definitions(-DDJIOSDK_MAJOR_VERSION=4)
add_definitions(-DDJIOSDK_MINOR_VERSION=1)
add_definitions(-DDJIOSDK_PATCH_VERSION=0)

add_definitions(-DDJIOSDK_IS_DEBUG=1)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "i386|i686|x86|AMD64|x86_64")
   set(ARCH x86)
   add_definitions(-DDJIOSDK_HARDWARE_TYPE=3)
elseif((CMAKE_SYSTEM_PROCESSOR MATCHES "^arm*") OR (CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch"))
  if(CMAKE_SIZEOF_VOID_P EQUAL 4)
     set(ARCH armv7)
     add_definitions(-DDJIOSDK_HARDWARE_TYPE=1)
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
     set(ARCH armv8)
     add_definitions(-DDJIOSDK_HARDWARE_TYPE=2)
  endif()
elseif()
  add_definitions(-DDJIOSDK_HARDWARE_TYPE=0)
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs)

set(ADVANCED_SENSING 1)

if (ADVANCED_SENSING)
  add_definitions(-DADVANCED_SENSING)
endif()

# DJI-SDK Core Libraries
add_subdirectory(osdk-core)

if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
  # Custom Core Functionality Path
  add_subdirectory(nucleus/modules)
endif()