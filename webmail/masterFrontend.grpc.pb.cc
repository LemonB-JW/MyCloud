// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: masterFrontend.proto

#include "masterFrontend.pb.h"
#include "masterFrontend.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace masterFrontend {

static const char* MasterFrontend_method_names[] = {
  "/masterFrontend.MasterFrontend/getServerList",
};

std::unique_ptr< MasterFrontend::Stub> MasterFrontend::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MasterFrontend::Stub> stub(new MasterFrontend::Stub(channel));
  return stub;
}

MasterFrontend::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_getServerList_(MasterFrontend_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MasterFrontend::Stub::getServerList(::grpc::ClientContext* context, const ::masterFrontend::getServerListRequest& request, ::masterFrontend::getServerListReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_getServerList_, context, request, response);
}

void MasterFrontend::Stub::experimental_async::getServerList(::grpc::ClientContext* context, const ::masterFrontend::getServerListRequest* request, ::masterFrontend::getServerListReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_getServerList_, context, request, response, std::move(f));
}

void MasterFrontend::Stub::experimental_async::getServerList(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::masterFrontend::getServerListReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_getServerList_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::masterFrontend::getServerListReply>* MasterFrontend::Stub::AsyncgetServerListRaw(::grpc::ClientContext* context, const ::masterFrontend::getServerListRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::masterFrontend::getServerListReply>::Create(channel_.get(), cq, rpcmethod_getServerList_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::masterFrontend::getServerListReply>* MasterFrontend::Stub::PrepareAsyncgetServerListRaw(::grpc::ClientContext* context, const ::masterFrontend::getServerListRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::masterFrontend::getServerListReply>::Create(channel_.get(), cq, rpcmethod_getServerList_, context, request, false);
}

MasterFrontend::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MasterFrontend_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MasterFrontend::Service, ::masterFrontend::getServerListRequest, ::masterFrontend::getServerListReply>(
          std::mem_fn(&MasterFrontend::Service::getServerList), this)));
}

MasterFrontend::Service::~Service() {
}

::grpc::Status MasterFrontend::Service::getServerList(::grpc::ServerContext* context, const ::masterFrontend::getServerListRequest* request, ::masterFrontend::getServerListReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace masterFrontend

