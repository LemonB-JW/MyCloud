cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(PennCloud CXX)
message(STATUS "${CMAKE_BUILD_TYPE} Build")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEIGEN_INITIALIZE_MATRICES_BY_NAN ")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include_directories(external/json/include)
include_directories(external/json)

add_subdirectory(frontendServer)
