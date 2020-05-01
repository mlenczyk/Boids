cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

set(NAME boids-project)

project(${NAME} CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(libs)
add_subdirectory(execs)

option(enable${name}Tests "This option controls whether the tests are enabled" OFF)
if(enable${name}Tests)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
else()
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)
endif()

file(COPY graphics DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})