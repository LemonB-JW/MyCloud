#include <iostream>
#include <memory>
#include <string>
#include <stdbool.h>
#include <grpcpp/grpcpp.h>
#include "../lib/FileMetaData.h"

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
using bigtable::GetFileListRequest;
using bigtable::GetFileListReply;
using bigtable::GetEmailListRequest;
using bigtable::GetEmailListReply;
using bigtable::Bigtable;

std::vector<FileMetaData> ListFileFromReply(const bigtable::GetFileListReply& file_list_reply) {
    std::vector<FileMetaData> file_list;

  for (int i = 0; i < file_list_reply.metadata_size(); i++) {
    const bigtable::fileMetaData& mdata = file_list_reply.metadata(i);

    cout << "File ID: " << mdata.file_id() << endl;
    cout << "  Name: " << mdata.file_name() << endl;
    FileMetaData file_info(mdata.created_time(), mdata.size(), mdata.file_name(), mdata.file_type(), mdata.file_from(), mdata.file_id());
    file_list.push_back(file_info);
   
  }

  return file_list;
}

std::vector<FileMetaData> ListEmailFromReply(const bigtable::GetEmailListReply& file_list_reply) {
    std::vector<FileMetaData> file_list;

  for (int i = 0; i < file_list_reply.metadata_size(); i++) {
    const bigtable::fileMetaData& mdata = file_list_reply.metadata(i);

    cout << "File ID: " << mdata.file_id() << endl;
    cout << "  Name: " << mdata.file_name() << endl;
    FileMetaData file_info(mdata.created_time(), mdata.size(), mdata.file_name(), mdata.file_type(), mdata.file_from(), mdata.file_id());
    file_list.push_back(file_info);
   
  }

  return file_list;
}


class TableClient {
 public:
  TableClient(std::shared_ptr<Channel> channel)
      : stub_(Bigtable::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  // bool put(string created_time, int size, string file_name, string file_type, string file_from, string row, string col, string data) {
  bool put(){ 
    // Data we are sending to the server.
    PutRequest request;
    request.set_created_time("2019/11/21");
    request.set_size(10);
    request.set_file_name("foo.txt");
    request.set_file_type("file");
    request.set_file_from("janice");
    request.set_row("alice");
    request.set_col("id2");
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

  std::vector<FileMetaData> list_files(){
    GetFileListRequest req;
    req.set_row("Janice");

    GetFileListReply reply;

    ClientContext context;

    // The actual RPC.
    Status status = stub_->list_all_files_for_currUser(&context, req, &reply);

    // Act upon its status.
    if (status.ok()) {
      return ListFileFromReply(reply);
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      std::vector<FileMetaData> v;
      return v;
    }

  }
  std::vector<FileMetaData> list_emails(){
    GetEmailListRequest req;
    req.set_row("Janice");

    GetEmailListReply reply;

    ClientContext context;

    // The actual RPC.
    Status status = stub_->list_all_emails_for_currUser(&context, req, &reply);

    // Act upon its status.
    if (status.ok()) {
      return ListEmailFromReply(reply);
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      std::vector<FileMetaData> v;
      return v;
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
  // bool reply = greeter.put("2019/11/20", 0, "foo.txt", "file", "alice", "janice", "id1", "Welcome"); //??
  bool reply = greeter.put();
  greeter.put();
  // bool reply2 = greeter.put("2019/11/20", 10, "boo.txt", "email", "alice", "ben", "id2", "Hello");
  std::string res = greeter.get();
  std::vector<FileMetaData> file_list = greeter.list_emails();
  std::cout << "Greeter received: " << reply << "  res is "<< res << " file list size is "<<file_list.size()<< std::endl;

  return 0;
}
