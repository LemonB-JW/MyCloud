cmake_minimum_required(VERSION 3.5.1)

# configure protoc
find_program(PROTOC_PLUGIN protoc)
if (NOT PROTOC_PLUGIN)
    message(FATAL_ERROR "protoc not found! please install it")
endif()
find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

# configure grpc
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin)
if (NOT GRPC_CPP_PLUGIN)
    message(FATAL_ERROR "grpc_cpp_plugin not found! please install it")
endif()
find_package(PkgConfig REQUIRED)
pkg_search_module(GRPC REQUIRED grpc)
pkg_search_module(GRPCPP REQUIRED grpc++)

# Proto file
get_filename_component(hw_proto "protos/bigtable.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/bigtable.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/bigtable.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/bigtable.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/bigtable.grpc.pb.h")
add_custom_command(
        OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
        COMMAND ${PROTOC_PLUGIN}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN}"
        "${hw_proto}"
        DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${Protobuf_INCLUDE_DIRS}")

foreach(_target
        bigtable_client bigtable_server)
    add_executable(${_target} "${_target}.cc"
            BigTable.cc
            Utility.cc
            ${hw_proto_srcs}
            ${hw_grpc_srcs})
    target_link_libraries(${_target} ${Protobuf_LIBRARIES})
    target_link_libraries(${_target} ${GRPCPP_LDFLAGS} ${GRPC_LDFLAGS})
endforeach()
