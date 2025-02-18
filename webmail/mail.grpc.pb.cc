// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: mail.proto

#include "mail.pb.h"
#include "mail.grpc.pb.h"

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
namespace mail {

static const char* Mail_method_names[] = {
  "/mail.Mail/GetMailList",
  "/mail.Mail/GetMail",
  "/mail.Mail/PutMail",
  "/mail.Mail/DeleteMail",
};

std::unique_ptr< Mail::Stub> Mail::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Mail::Stub> stub(new Mail::Stub(channel));
  return stub;
}

Mail::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_GetMailList_(Mail_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetMail_(Mail_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_PutMail_(Mail_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DeleteMail_(Mail_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Mail::Stub::GetMailList(::grpc::ClientContext* context, const ::mail::GetMailListRequest& request, ::mail::GetMailListReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetMailList_, context, request, response);
}

void Mail::Stub::experimental_async::GetMailList(::grpc::ClientContext* context, const ::mail::GetMailListRequest* request, ::mail::GetMailListReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetMailList_, context, request, response, std::move(f));
}

void Mail::Stub::experimental_async::GetMailList(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::mail::GetMailListReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetMailList_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::mail::GetMailListReply>* Mail::Stub::AsyncGetMailListRaw(::grpc::ClientContext* context, const ::mail::GetMailListRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::mail::GetMailListReply>::Create(channel_.get(), cq, rpcmethod_GetMailList_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::mail::GetMailListReply>* Mail::Stub::PrepareAsyncGetMailListRaw(::grpc::ClientContext* context, const ::mail::GetMailListRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::mail::GetMailListReply>::Create(channel_.get(), cq, rpcmethod_GetMailList_, context, request, false);
}

::grpc::Status Mail::Stub::GetMail(::grpc::ClientContext* context, const ::mail::GetMailRequest& request, ::mail::GetMailReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetMail_, context, request, response);
}

void Mail::Stub::experimental_async::GetMail(::grpc::ClientContext* context, const ::mail::GetMailRequest* request, ::mail::GetMailReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetMail_, context, request, response, std::move(f));
}

void Mail::Stub::experimental_async::GetMail(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::mail::GetMailReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetMail_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::mail::GetMailReply>* Mail::Stub::AsyncGetMailRaw(::grpc::ClientContext* context, const ::mail::GetMailRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::mail::GetMailReply>::Create(channel_.get(), cq, rpcmethod_GetMail_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::mail::GetMailReply>* Mail::Stub::PrepareAsyncGetMailRaw(::grpc::ClientContext* context, const ::mail::GetMailRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::mail::GetMailReply>::Create(channel_.get(), cq, rpcmethod_GetMail_, context, request, false);
}

::grpc::Status Mail::Stub::PutMail(::grpc::ClientContext* context, const ::mail::PutMailRequest& request, ::mail::PutMailReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_PutMail_, context, request, response);
}

void Mail::Stub::experimental_async::PutMail(::grpc::ClientContext* context, const ::mail::PutMailRequest* request, ::mail::PutMailReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_PutMail_, context, request, response, std::move(f));
}

void Mail::Stub::experimental_async::PutMail(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::mail::PutMailReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_PutMail_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::mail::PutMailReply>* Mail::Stub::AsyncPutMailRaw(::grpc::ClientContext* context, const ::mail::PutMailRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::mail::PutMailReply>::Create(channel_.get(), cq, rpcmethod_PutMail_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::mail::PutMailReply>* Mail::Stub::PrepareAsyncPutMailRaw(::grpc::ClientContext* context, const ::mail::PutMailRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::mail::PutMailReply>::Create(channel_.get(), cq, rpcmethod_PutMail_, context, request, false);
}

::grpc::Status Mail::Stub::DeleteMail(::grpc::ClientContext* context, const ::mail::DeleteMailRequest& request, ::mail::DeleteMailReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_DeleteMail_, context, request, response);
}

void Mail::Stub::experimental_async::DeleteMail(::grpc::ClientContext* context, const ::mail::DeleteMailRequest* request, ::mail::DeleteMailReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DeleteMail_, context, request, response, std::move(f));
}

void Mail::Stub::experimental_async::DeleteMail(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::mail::DeleteMailReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DeleteMail_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::mail::DeleteMailReply>* Mail::Stub::AsyncDeleteMailRaw(::grpc::ClientContext* context, const ::mail::DeleteMailRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::mail::DeleteMailReply>::Create(channel_.get(), cq, rpcmethod_DeleteMail_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::mail::DeleteMailReply>* Mail::Stub::PrepareAsyncDeleteMailRaw(::grpc::ClientContext* context, const ::mail::DeleteMailRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::mail::DeleteMailReply>::Create(channel_.get(), cq, rpcmethod_DeleteMail_, context, request, false);
}

Mail::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Mail_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Mail::Service, ::mail::GetMailListRequest, ::mail::GetMailListReply>(
          std::mem_fn(&Mail::Service::GetMailList), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Mail_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Mail::Service, ::mail::GetMailRequest, ::mail::GetMailReply>(
          std::mem_fn(&Mail::Service::GetMail), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Mail_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Mail::Service, ::mail::PutMailRequest, ::mail::PutMailReply>(
          std::mem_fn(&Mail::Service::PutMail), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Mail_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Mail::Service, ::mail::DeleteMailRequest, ::mail::DeleteMailReply>(
          std::mem_fn(&Mail::Service::DeleteMail), this)));
}

Mail::Service::~Service() {
}

::grpc::Status Mail::Service::GetMailList(::grpc::ServerContext* context, const ::mail::GetMailListRequest* request, ::mail::GetMailListReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Mail::Service::GetMail(::grpc::ServerContext* context, const ::mail::GetMailRequest* request, ::mail::GetMailReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Mail::Service::PutMail(::grpc::ServerContext* context, const ::mail::PutMailRequest* request, ::mail::PutMailReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Mail::Service::DeleteMail(::grpc::ServerContext* context, const ::mail::DeleteMailRequest* request, ::mail::DeleteMailReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace mail

