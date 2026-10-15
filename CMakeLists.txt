cmake_minimum_required(VERSION 3.16)
project(vhlibmetacrc VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/version_vhmetacrc.h"
)

add_library(vhlib_metacrc STATIC
    src/vhmetablock_crc16.cpp
    src/vhmetablock.cpp
    src/vhmetablock_cache.cpp
)

target_include_directories(vhlib_metacrc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    "${CMAKE_CURRENT_BINARY_DIR}/generated"
)
