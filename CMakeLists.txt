cmake_minimum_required(VERSION 3.29)
project(vizo C)

set(CMAKE_C_STANDARD 17)
include_directories(include)

execute_process(
        COMMAND python3 -c "import sys; print(sys.base_prefix, end='')"
        OUTPUT_VARIABLE PYTHON_PREFIX
)

execute_process(
        COMMAND python3 -c "import sys; print(sys.version_info.major, end='')"
        OUTPUT_VARIABLE PYTHON_VERSION_MAJOR
)

execute_process(
        COMMAND python3 -c "import sys; print(sys.version_info.minor, end='')"
        OUTPUT_VARIABLE PYTHON_VERSION_MINOR
)

set(PYTHON_VERSION ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR})
set(PYTHON_INCLUDE_DIR ${PYTHON_PREFIX}/include/python${PYTHON_VERSION})
set(PYTHON_LIB_DIR ${PYTHON_PREFIX}/lib)


include_directories(${PYTHON_INCLUDE_DIR})
link_directories(${PYTHON_LIB_DIR})

add_executable(vizo
        include/vizo/package/package_info.h
        include/vizo/util/json.h
        src/package/package_info.c
        src/util/json.c
        src/main.c
        include/vizo/package/package.h
        include/vizo/package/dependency.h
        src/package/dependency.c
        include/vizo/build/build.h
        include/vizo/util/lists.h
        src/util/list.c
        src/build/build.c
        include/vizo/package/profile.h
        include/vizo/package/target.h
)

target_link_libraries(vizo python${PYTHON_VERSION})
