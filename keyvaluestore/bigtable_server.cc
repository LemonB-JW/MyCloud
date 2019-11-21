// Author: Jiaying Guo

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>
// #include "../lib/FileMetaData.h"
#include "../lib/BigTable.h"
#include "../lib/Utility.h"

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
using bigtable::GetFileListRequest;
using bigtable::GetFileListReply;
using bigtable::GetEmailListRequest;
using bigtable::GetEmailListReply;
using bigtable::Bigtable;


BigTable table;

// This function fills in a Person message based on user input.
void ConstructMetaDataResponse(bigtable::fileMetaData* fileMetaData, FileMetaData srcData) {
  fileMetaData->set_file_name(srcData.file_name);
  fileMetaData->set_size(srcData.size);
  fileMetaData->set_file_type(srcData.file_type);
  fileMetaData->set_file_id(srcData.file_id);
  fileMetaData->set_created_time(srcData.created_time);
  fileMetaData->set_file_from(srcData.file_from);

}

// Logic and data behind the server's behavior.
class TableServiceImpl final : public Bigtable::Service {
  Status put(ServerContext* context, const PutRequest* request,
                  PutReply* reply) override {
    // std::string prefix("Hello ");
    bool ret = table.put(request->created_time(), request->size(), request->file_name(), request->file_type(), request->file_from(), request->row(), request->col(), request->data());
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

  Status list_all_files_for_currUser(ServerContext* context, const GetFileListRequest* request,
                  GetFileListReply* reply) override {
    // std::string prefix("Hello ");
    vector<FileMetaData> res = table.list_all_files_for_currUser(request->row());
    cout<<"request row is "<<request->row()<<" res size is "<<res.size()<<endl;
    for(int i = 0; i < res.size(); i++){
      cout<<res.at(i).file_name<<endl;
      ConstructMetaDataResponse(reply->add_metadata(), res.at(i));
    }
    return Status::OK;
  }

   Status list_all_emails_for_currUser(ServerContext* context, const GetEmailListRequest* request,
                  GetEmailListReply* reply) override {
    // std::string prefix("Hello ");
    vector<FileMetaData> res = table.list_all_emails_for_currUser(request->row());
    cout<<"request row is "<<request->row()<<" res size is "<<res.size()<<endl;
    for(int i = 0; i < res.size(); i++){
      cout<<res.at(i).file_name<<endl;
      ConstructMetaDataResponse(reply->add_metadata(), res.at(i));
    }
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("127.0.0.1:50051");
  table.put("2019/11/20", 10, "foo.txt", "email", "Alice", "Janice", Utility::generateFileID(1 , 1), "Hello from Janice, welcome to penn_cloud.");
  table.put("2019/11/20", 10, "foo.txt", "email", "Alice", "Janice", Utility::generateFileID(1 , 1), "Hello from Janice, welcome to penn_cloud.");
  table.put("2019/11/21", 15, "boo.txt", "email", "Janice", "Ben", Utility::generateFileID(2 , 2), "Hello from Bennn, welcome to penn_cloud.");
  table.put("2019/11/21", 20, "Welcome on board", "email", "Janice", "Alice", Utility::generateFileID(2 , 3), "Hello from Alice, welcome to penn_cloud.");
  table.put("2019/11/21", 23, "Welcome on board", "email", "Janice", "John", Utility::generateFileID(2 , 4), "Hello from Johnnn, welcome to penn_cloud.");
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
