cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(PennCloud CXX)
message(STATUS "${CMAKE_BUILD_TYPE} Build")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEIGEN_INITIALIZE_MATRICES_BY_NAN ")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include_directories(external/json/include)
include_directories(external/json)

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