// Author: Jiaying Guo

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>
// #include "../lib/FileMetaData.h"
#include "../lib/DistributedStorage.h"

#ifdef BAZEL_BUILD
#include "bigtable.grpc.pb.h"
#else
#include "bigtable.grpc.pb.h"
#endif

using grpc::ClientContext;
using grpc::Channel;
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
using bigtable::RenameFifoRequest;
using bigtable::RenameFifoReply;
using bigtable::MoveFifoRequest;
using bigtable::MoveFifoReply;
using bigtable::Bigtable;
using bigtable::LocalPutWithIDRequest;
using bigtable::LocalPutWithIDReply;


DistributedStorage* storage = new DistributedStorage();
int v_flag = 0;
// This function fills in a Person message based on user input.
void ConstructMetaDataResponse(bigtable::fileMetaData* fileMetaData, FileMetaData srcData) {
  fileMetaData->set_file_name(srcData.file_name);
  fileMetaData->set_size(srcData.size);
  fileMetaData->set_file_type(srcData.file_type);
  fileMetaData->set_file_id(srcData.file_id);
  fileMetaData->set_created_time(srcData.created_time);
  fileMetaData->set_file_from(srcData.file_from);

}

class TableClient {
 public:
  TableClient(std::shared_ptr<Channel> channel)
      : stub_(Bigtable::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  // bool put(string created_time, int size, string file_name, string file_type, string file_from, string row, string col, string data) {
  std::string put(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string user,
    std::string file_content){
    // Data we are sending to the server.
    PutRequest request;
    request.set_created_time(created_time);
    request.set_size(size);
    request.set_path_name(file_name);
    request.set_file_type(file_type);
    request.set_file_from(file_from);
    request.set_row(user);
    request.set_data(file_content);


    // Container for the data we expect from the server.
    PutReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->put(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.file_id();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string localPut_with_fileid(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string user,
    std::string file_id, std::string file_content){
    // Data we are sending to the server.
    LocalPutWithIDRequest request;
    request.set_created_time(created_time);
    request.set_size(size);
    request.set_path_name(file_name);
    request.set_file_type(file_type);
    request.set_file_from(file_from);
    request.set_row(user);
    request.set_col(file_id);
    request.set_data(file_content);


    // Container for the data we expect from the server.
    LocalPutWithIDReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->localPut_with_fileid(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.file_id();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Bigtable::Stub> stub_;
};


// class StorageServiceImpl final : public Storage::Service{
//   Status localPut_with_fileid(ServerContext* context, const LocalPutWithIDRequest* request,
//                   LocalPutWithIDReply* reply) override {
//     std::string file_id = storage->localPut_with_fileid(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->col(), request->data())
//     reply->set_file_id(file_id);
//     return Status::OK;
//   }
// }

// class StorageClient {
//  public:
//   StorageClient(std::shared_ptr<Channel> channel)
//       : stub_(Storage::NewStub(channel)) {}

//   // Assembles the client's payload, sends it and presents the response back
//   // from the server.
//   // bool put(string created_time, int size, string file_name, string file_type, string file_from, string row, string col, string data) {
//   std::string localPut_with_fileid(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string user,
//     std::string file_id, std::string file_content){
//     // Data we are sending to the server.
//     LocalPutWithIDRequest request;
//     request.set_created_time(created_time);
//     request.set_size(size);
//     request.set_file_name(file_name);
//     request.set_file_type(file_type);
//     request.set_file_from(file_from);
//     request.set_row(user);
//     request.set_col(file_id);
//     request.set_data(file_content);


//     // Container for the data we expect from the server.
//     LocalPutWithIDReply reply;

//     // Context for the client. It could be used to convey extra information to
//     // the server and/or tweak certain RPC behaviors.
//     ClientContext context;

//     // The actual RPC.
//     Status status = stub_->put(&context, request, &reply);

//     // Act upon its status.
//     if (status.ok()) {
//       return reply.file_id();
//     } else {
//       std::cout << status.error_code() << ": " << status.error_message()
//                 << std::endl;
//       return "RPC failed";
//     }
//   }

//  private:
//   std::unique_ptr<Storage::Stub> stub_;
// };

// Logic and data behind the server's behavior.
class TableServiceImpl final : public Bigtable::Service {
  Status put(ServerContext* context, const PutRequest* request,
                  PutReply* reply) override {

    // primary get mutli req from same user (diff nodes), primary sort them and send the order of req to other nodes
    // 3,2,1 -> every worker node process in the same order ?? when will the worker node will respond to front-end client?
    // primary send out req 3, w1 proc 3, w2 (3) proc 3, send ok back primary -> primary send ok to w2->respond to client
    // forward request to primary and wait for ok and order from primary
    // only primary node gets to generate file_id, then pass it to other worker nodes.
    std::string file_id;
    if(!storage->is_primary){
        // forward to primary node, call primary node grpc server_put()
        std::string primary_full_ip = storage->primary_addr->ip + ":" + std::to_string(storage->primary_addr->port);
        TableClient primary_node(grpc::CreateChannel(primary_full_ip, grpc::InsecureChannelCredentials()));
        std::string inner_rpc_reply = primary_node.put(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->data());
        while(inner_rpc_reply == "RPC failed"){
          primary_node.put(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->data());
        }
    }else{
        file_id = storage->localPut(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->data());
        for(int i = 0; i < storage->all_sub_addr.size(); i++){
          std::string curr_sub_addr = storage->all_sub_addr.at(i).ip + ":" + std::to_string(storage->all_sub_addr.at(i).port);
          TableClient worker_node(grpc::CreateChannel(curr_sub_addr, grpc::InsecureChannelCredentials()));
          std::string inner_rpc_reply = worker_node.localPut_with_fileid(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), file_id, request->data());
          while(inner_rpc_reply == "RPC failed"){
            inner_rpc_reply = worker_node.localPut_with_fileid(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), file_id, request->data());
          }
      }
    }
   
    reply->set_file_id(file_id);
    return Status::OK;
  }

  Status get(ServerContext* context, const GetRequest* request,
                  GetReply* reply) override {
    // std::string prefix("Hello ");
    std::string res = storage->table.get(request->row(), request->col());
    reply->set_file_content(res);
    return Status::OK;
  }

  Status list_all_files(ServerContext* context, const GetFileListRequest* request,
                  GetFileListReply* reply) override {
    // std::string prefix("Hello ");
    vector<FileMetaData> res = storage->table.list_all_files(request->row(), request->path_name());
    // cout<<"request row is "<<request->row()<<" res size is "<<res.size()<<endl;
    if(!res.empty()){
      for(int i = 0; i < res.size(); i++){
        std::cout<<res.at(i).file_name<<std::endl;
        ConstructMetaDataResponse(reply->add_metadata(), res.at(i));
      }
    }else{
      std::cout<<"file/folder not exists!!"<<std::endl;
    }
    
    return Status::OK;
  }

   Status list_all_emails(ServerContext* context, const GetEmailListRequest* request,
                  GetEmailListReply* reply) override {
      
      vector<FileMetaData> res = storage->table.list_all_emails(request->row());
      // cout<<"request row is "<<request->row()<<" res size is "<<res.size()<<endl;
      if(!res.empty()){
        for(int i = 0; i < res.size(); i++){
          std::cout<<res.at(i).file_name<<std::endl;
          ConstructMetaDataResponse(reply->add_metadata(), res.at(i));
        }
      }else{
        std::cout<<"file/folder not exists!!"<<std::endl;
      }

      return Status::OK;
  }

   Status rename_file_folder(ServerContext* context, const RenameFifoRequest* request,
                  RenameFifoReply* reply) override {
      bool res = storage->table.rename_file_folder(request->row(), request->file_type(), request->path_name(), request->new_file_name());
      reply->set_is_successful(res);
      return Status::OK;
   }

   Status move_file_folder(ServerContext* context, const MoveFifoRequest* request,
                  MoveFifoReply* reply) override {
      bool res = storage->table.move_file_folder(request->row(), request->file_type(), request->path_name(), request->new_path());
      reply->set_is_successful(res);
      return Status::OK;
   }

   Status localPut_with_fileid(ServerContext* context, const LocalPutWithIDRequest* request,
                  LocalPutWithIDReply* reply) override {
    std::string file_id = storage->localPut_with_fileid(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->col(), request->data());
    reply->set_file_id(file_id);
    return Status::OK;
  }

};

void RunStorageServer(std::string server_addr) {

  std::string server_address(server_addr);
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
  // read config file: 1st addr for front-end, 2nd addr for back-end
  // identify self is primary or not, if so, get subordinate node list of indices. else, get index of prim node
  if (argc < 2) {
    fprintf(stderr, "*** Author: Jiaying Guo (gjying)\n");
    // cleanup();
    exit(1);
  }
  
  // parse arguments of command line
  int c;
  while ((c = getopt (argc, argv, "v")) != -1){
    switch (c){
      case 'v':
        v_flag = 1;
        break;
      case '?':
        default:
          abort ();
     }
  }
  
  
  if(optind >= argc){
    fprintf(stderr, "Invalid terminal input. Please check and try again!\n");
      exit(1);
    return 1;
  }

  const char* config_file = argv[optind];
  const char* index = argv[optind + 1];
  storage->readConfigFile(config_file, index);
  // master client call rpc get primary 
  storage->updatePrimary(1);

  std::string self_full_ip = storage->self_addr.ip + ":" + std::to_string(storage->self_addr.port);
  RunStorageServer(self_full_ip);

  return 0;
}
