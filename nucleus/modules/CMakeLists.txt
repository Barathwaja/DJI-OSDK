cmake_minimum_required(VERSION 2.8)
project(onboardsdk-custom-modules)


include_directories(${DJIOSDK_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/hal)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/osal)


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

set(OSDK_CORE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../osdk-core)
set(CMAKE_MODULE_PATH ${OSDK_CORE_PATH}/cmake-modules)


message("-----------OSDK_LIB_HEADERS_DIR------------")
set(OSDK_LIB_HEADERS_DIR
        ${OSDK_CORE_PATH}/api/inc
        ${OSDK_CORE_PATH}/modules/inc/payload
        ${OSDK_CORE_PATH}/modules/inc/flight
        ${OSDK_CORE_PATH}/modules/inc/mop
        ${OSDK_CORE_PATH}/platform/inc
        ${OSDK_CORE_PATH}/logger/inc
        ${OSDK_CORE_PATH}/utility/inc
        ${OSDK_CORE_PATH}/linker/${ARCH}/inc
        ${OSDK_CORE_PATH}/modules/inc/filemgr
        )
include_directories(${OSDK_LIB_HEADERS_DIR})
message((${OSDK_LIB_HEADERS_DIR}))


# message("\n-----------ADVANCED_SENSING_HEADERS_DIR------------")
# set(ADVANCED_SENSING_SOURCE_ROOT ${OSDK_CORE_PATH}/advanced-sensing)
# set(ADVANCED_SENSING_HEADERS_DIR
#     ${ADVANCED_SENSING_SOURCE_ROOT}/api/inc
#     ${ADVANCED_SENSING_SOURCE_ROOT}/platform/inc
#     ${ADVANCED_SENSING_SOURCE_ROOT}/protocol/inc
#     ${ADVANCED_SENSING_SOURCE_ROOT}/camera_stream/src
#     ${ADVANCED_SENSING_SOURCE_ROOT}/ori-osdk-core/protocol/inc
#     ${ADVANCED_SENSING_SOURCE_ROOT}/ori-osdk-core/hal/inc
#     ${ADVANCED_SENSING_SOURCE_ROOT}/ori-osdk-core/platform/linux/inc
#     )
# include_directories(${ADVANCED_SENSING_HEADERS_DIR})
# message((${ADVANCED_SENSING_HEADERS_DIR}))

# find_package(LibUSB REQUIRED)
# find_package(FFMPEG REQUIRED)

# if(FFMPEG_FOUND)
#     message(STATUS "Found FFmpeg ${FFMPEG_VERSION} installed in the system.")
#     message(STATUS " - Includes: ${FFMPEG_INCLUDE_DIRS}")
#     message(STATUS " - Libraries: ${FFMPEG_LIBRARIES}")
# else()
#     message("Cannot Find FFMPEG")
# endif(FFMPEG_FOUND)

# include_directories(${LIBUSB_1_INCLUDE_DIRS})
# include_directories(${FFMPEG_INCLUDE_DIR})

# if(ADVANCED_SENSING)
#     link_libraries(advanced-sensing)
#     link_libraries(djiosdk-core)
#     link_libraries(${LIBUSB_1_LIBRARIES})
#     link_libraries(${FFMPEG_LIBRARIES})
# endif()

if (OSDK_HOTPLUG)
    add_definitions(-DOSDK_HOTPLUG)
    message("\n-- Enable OSDK Hotplug monitoring.")
    find_package(LibUDEV REQUIRED)
    include_directories(${LIBUDEV_INCLUDE_DIRS})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/hal/hotplug)
    link_libraries(${LIBUDEV_LIBRARIES})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ludev")
else ()
    message("\n-- You can cmake with \"-DOSDK_HOTPLUG=ON\" to enable OSDK Hotplug monitoring for linux platform.")
endif ()


if (CONFIG_TOOL)
    message("\n-- Rebuild the config tool")
    add_subdirectory(config_tool)
else()
    message("\n-- You can cmake with \"-DCONFIG_TOOL=ON\" to rebuild the config tool.")
endif()

# Custom Modules Path
message("IMPORTING MODULES")
add_subdirectory(telemetry)