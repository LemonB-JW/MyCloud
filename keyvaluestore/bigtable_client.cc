#include <iostream>
#include <memory>
#include <string>
#include <stdbool.h>
#include <grpcpp/grpcpp.h>
// #include "protos/bigtable.pb.h"

// #ifdef BAZEL_BUILD
// #include "bigtable.grpc.pb.h"
// #endif

#ifdef BAZEL_BUILD
#include "bigtable.grpc.pb.h"
#else
#include "bigtable.grpc.pb.h"
#endif




using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using bigtable::PutRequest;
using bigtable::PutReply;
using bigtable::GetRequest;
using bigtable::GetReply;
using bigtable::Bigtable;

class TableClient {
 public:
  TableClient(std::shared_ptr<Channel> channel)
      : stub_(Bigtable::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  bool put() {
    // Data we are sending to the server.
    PutRequest request;
    request.set_created_time("2019/11/20");
    request.set_size(10);
    request.set_file_name("foo.txt");
    request.set_file_type("file");
    request.set_row("alice");
    request.set_col("foo.txt");
    request.set_data("Welcome");


    // Container for the data we expect from the server.
    PutReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->put(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.ret();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return false;
    }
  }

  std::string get(){
    GetRequest req;
    req.set_row("alice");
    req.set_col("foo.txt");

    GetReply reply;

    ClientContext context;

    // The actual RPC.
    Status status = stub_->get(&context, req, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.content();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }

  }

 private:
  std::unique_ptr<Bigtable::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  TableClient greeter(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  bool reply = greeter.put();
  std::string res = greeter.get();
  std::cout << "Greeter received: " << reply << "  res is "<< res << std::endl;

  return 0;
}
