cmake_minimum_required(VERSION 2.8)

project(Test)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(OpenCL REQUIRED)

include_directories( ${OPENCL_INCLUDE_DIRS} include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O3")

add_executable(Test main.cpp)

target_link_libraries(Test ${OPENCL_LIBRARIES})
