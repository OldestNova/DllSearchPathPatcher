cmake_minimum_required(VERSION 3.29)
project(DllSearchPathPatcher)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

add_library(DllSearchPathPatcher SHARED VersionLoader.cpp)
target_link_libraries(DllSearchPathPatcher PRIVATE kernel32)
set_target_properties(DllSearchPathPatcher PROPERTIES
        OUTPUT_NAME "version"
        PREFIX ""
)