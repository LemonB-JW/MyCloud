// Author: Jiaying Guo

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "../lib/BigTable.h"


#ifdef BAZEL_BUILD
#include "bigtable.grpc.pb.h"
#else
#include "bigtable.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using bigtable::PutRequest;
using bigtable::PutReply;
using bigtable::GetRequest;
using bigtable::GetReply;
using bigtable::Bigtable;


BigTable table;


// Logic and data behind the server's behavior.
class TableServiceImpl final : public Bigtable::Service {
  Status put(ServerContext* context, const PutRequest* request,
                  PutReply* reply) override {
    // std::string prefix("Hello ");
    bool ret = table.put(request->created_time(), request->size(), request->file_name(), request->file_type(), request->row(), request->col(), request->data());
    reply->set_ret(ret);
    return Status::OK;
  }

  Status get(ServerContext* context, const GetRequest* request,
                  GetReply* reply) override {
    // std::string prefix("Hello ");
    std::string res = table.get(request->row(), request->col());
    reply->set_content(res);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("127.0.0.1:50051");
  TableServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
