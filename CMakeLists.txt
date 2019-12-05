cmake_minimum_required(VERSION 3.5.1  FATAL_ERROR)

project(PennCloud CXX)
message(STATUS "${CMAKE_BUILD_TYPE} Build")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEIGEN_INITIALIZE_MATRICES_BY_NAN ")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# configure protoc
find_program(PROTOC_PLUGIN protoc)
if (NOT PROTOC_PLUGIN)
    message(FATAL_ERROR "protoc not found! please install it")
endif()
find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

# configure grpc
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
if (NOT GRPC_CPP_PLUGIN)
    message(FATAL_ERROR "grpc_cpp_plugin not found! please install it")
endif()
find_package(PkgConfig REQUIRED)
pkg_search_module(GRPCPP REQUIRED grpc++)

# add json dependency
include_directories(external/json/include)
include_directories(external/json)

# add threads
find_package(Threads)

function(add_penn_cloud_executable binary)
    add_executable(${binary} ${ARGN})
    set_target_properties(${binary} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    set_target_properties(${binary} PROPERTIES DEBUG_POSTFIX _debug)
    set_target_properties(${binary} PROPERTIES COVERAGE_POSTFIX _coverage)
    set_target_properties(${binary} PROPERTIES QUICK_POSTFIX _quick)
    set_target_properties(${binary} PROPERTIES RELWITHDEBINFO_POSTFIX _reldeb)
    set_target_properties(${binary} PROPERTIES MINSIZEREL_POSTFIX _min)
    install(TARGETS ${binary} DESTINATION bin)
endfunction(add_penn_cloud_executable)

add_subdirectory(frontendServer)
add_subdirectory(keyvaluestore)
add_subdirectory(webmail)