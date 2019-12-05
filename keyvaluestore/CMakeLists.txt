# Generated Proto sources
foreach(_target
        bigtable masterBackend)
    get_filename_component(hw_proto "protos/${_target}.proto" ABSOLUTE)
    get_filename_component(hw_proto_path "${hw_proto}" PATH)
    set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${_target}.pb.cc")
    set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${_target}.pb.h")
    set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${_target}.grpc.pb.cc")
    set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${_target}.grpc.pb.h")
    set(all_hw_proto_srcs "${all_hw_proto_srcs};${hw_proto_srcs}")
    set(all_hw_grpc_srcs "${all_hw_grpc_srcs};${hw_grpc_srcs}")
    add_custom_command(
            OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
            COMMAND ${PROTOC_PLUGIN}
            ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
            --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
            -I "${hw_proto_path}"
            --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN}"
            "${hw_proto}"
            DEPENDS "${hw_proto}")
endforeach()

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
include_directories("${Protobuf_INCLUDE_DIRS}")

foreach(_target
        bigtable_client bigtable_server)
    add_penn_cloud_executable(${_target} "${_target}.cc"
            BigTable.cc
            Utility.cc
            DistributedStorage.cc
            MetaTree.cc
            ${all_hw_proto_srcs}
            ${all_hw_grpc_srcs})
    target_link_libraries(${_target} ${Protobuf_LIBRARIES})
    target_link_libraries(${_target} ${GRPCPP_LDFLAGS})
endforeach()
