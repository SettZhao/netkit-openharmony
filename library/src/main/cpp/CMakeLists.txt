# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(myNpmLib)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(library SHARED napi_init.cpp
socket/dns.cpp
socket/dns.h
utils/hilog_helper.h
utils/hilog_helper.cpp
error/network_exception.h
error/network_exception.cpp)
target_link_libraries(library PUBLIC libace_napi.z.so libhilog_ndk.z.so)
