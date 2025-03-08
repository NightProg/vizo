cmake_minimum_required(VERSION 3.29)
project(vizo C)

set(CMAKE_C_STANDARD 17)
include_directories(include)
add_executable(vizo main.c
        include/vizo/package/package_info.h
        include/vizo/package/json.h
        src/package/package_info.c)
