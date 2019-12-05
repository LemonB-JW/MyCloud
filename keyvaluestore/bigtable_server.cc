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
#include "masterBackend.grpc.pb.h"
#else
#include "bigtable.grpc.pb.h"
#include "masterBackend.grpc.pb.h"
#endif

using grpc::ClientContext;
using grpc::Channel;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using bigtable::Bigtable;
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
using bigtable::LocalPutWithIDRequest;
using bigtable::LocalPutWithIDReply;
using bigtable::DelRequest;
using bigtable::DelReply;
using bigtable::CPutRequest;
using bigtable::CPutReply;
using bigtable::LocalCPutRequest;
using bigtable::LocalCPutReply;
using bigtable::LocalDelRequest;
using bigtable::LocalDelReply;
using bigtable::LocalRenameRequest;
using bigtable::LocalRenameReply;
using bigtable::LocalMoveRequest;
using bigtable::LocalMoveReply;

using masterBackend::MasterBackend;
using masterBackend::GetPrimRequest;
using masterBackend::GetPrimReply;
using masterBackend::ListSubRequest;
using masterBackend::ListSubReply;

DistributedStorage* storage = new DistributedStorage();
int v_flag = 0;

class MBcommuClient {
  public:
    MBcommuClient(std::shared_ptr<Channel> channel):stub_(MasterBackend::NewStub(channel)){}
  
  int get_prim(int myindex){
    GetPrimRequest request;
    
    request.set_my_index(myindex);
    ClientContext context;
    GetPrimReply reply;
    Status status = stub_->get_prim(&context, request, &reply);
    
    if(status.ok()){
      return reply.prim_index();
    }else{
      std::cout << status.error_code() << ": " << status.error_message() << std::endl;
      return -1;
    }
  }
  
  std::vector<int> list_sub(int myindex){
    ListSubRequest request;
    
    request.set_my_index(myindex);
    ClientContext context;
    ListSubReply reply;
    Status status = stub_->list_sub(&context, request, &reply);
    
    if(status.ok()){
      std::vector<int> response;
      for (int i = 0; i< reply.sub_index_size(); i++){
        response.push_back(reply.sub_index(i));
      }
      return response;
    }else{
      std::cout << status.error_code() << ": " << status.error_message() << std::endl;
      std::vector<int> err;//return empty vector when error???
      return err;
    }
  }
  
  private:
    std::unique_ptr<MasterBackend::Stub> stub_;
};

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

  std::string cput(std::string new_created_time, int new_size, std::string path_name, std::string file_type, std::string row, std::string col,
    std::string old_data, std::string new_data){
    CPutRequest request;
    request.set_new_created_time(new_created_time);
    request.set_new_size(new_size);
    request.set_path_name(path_name);
    request.set_file_type(file_type); 
    request.set_row(row);
    request.set_col(col);
    request.set_old_data(old_data);
    request.set_new_data(new_data);


    // Container for the data we expect from the server.
    CPutReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->cput(&context, request, &reply);

    // std:string res = (bool) reply.is_successful() ? "true" : "false";
    if (status.ok()) {
      std::string res = "";
      if(reply.is_successful()){
        res = "true";
      }else{
        res = "false";
      }     
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string table_delete(std::string row, std::string col, std::string file_type, std::string path_name){
    DelRequest request;
    request.set_path_name(path_name);
    request.set_file_type(file_type); 
    request.set_row(row);
    request.set_col(col);
   


    // Container for the data we expect from the server.
    DelReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->table_delete(&context, request, &reply);

   // Act upon its status.
    if (status.ok()) {
      std::string res = "";
      if(reply.is_successful()){
        res = "true";
      }else{
        res = "false";
      }     
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }


  std::string rename_file_folder(std::string row, std::string file_type, std::string path_name, std::string new_file_name){
    RenameFifoRequest request;
    request.set_path_name(path_name);
    request.set_file_type(file_type); 
    request.set_row(row);
    request.set_new_file_name(new_file_name);
   


    // Container for the data we expect from the server.
    RenameFifoReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->rename_file_folder(&context, request, &reply);

   // Act upon its status.
    if (status.ok()) {
      std::string res = "";
      if(reply.is_successful()){
        res = "true";
      }else{
        res = "false";
      }     
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string move_file_folder(std::string row, std::string file_type, std::string path_name, std::string new_path){
    MoveFifoRequest request;
    request.set_path_name(path_name);
    request.set_file_type(file_type); 
    request.set_row(row);
    request.set_new_path(new_path);
   


    // Container for the data we expect from the server.
    MoveFifoReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->move_file_folder(&context, request, &reply);

   // Act upon its status.
    if (status.ok()) {
      std::string res = "";
      if(reply.is_successful()){
        res = "true";
      }else{
        res = "false";
      }     
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string localPut_with_fileid(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string user,
    std::string file_id, std::string file_content){
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




  std::string localCPut(std::string new_created_time, int new_size, std::string path_name, std::string file_type, std::string row, std::string col,
    std::string old_data, std::string new_data){
    // Data we are sending to the server.
    LocalCPutRequest request;
    request.set_new_created_time(new_created_time);
    request.set_new_size(new_size);
    request.set_path_name(path_name);
    request.set_file_type(file_type); 
    request.set_row(row);
    request.set_col(col);
    request.set_old_data(old_data);
    request.set_new_data(new_data);


    // Container for the data we expect from the server.
    LocalCPutReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->localCPut(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      std::string res = "";
      if(reply.is_successful()){
        res = "true";
      }else{
        res = "false";
      }     
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }


  std::string localDelete(std::string row, std::string col,
    std::string file_type, std::string path_name){
    // Data we are sending to the server.
    LocalDelRequest request;
    request.set_path_name(path_name);
    request.set_file_type(file_type);
    request.set_row(row);
    request.set_col(col);



    // Container for the data we expect from the server.
    LocalDelReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->localDelete(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      std::string res = "";
      if(reply.is_successful()){
        res = "true";
      }else{
        res = "false";
      }  
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string localRenameFifo(std::string row,  std::string file_type, std::string path_name, std::string new_file_name){
    // Data we are sending to the server.
    LocalRenameRequest request;
    request.set_path_name(path_name);
    request.set_file_type(file_type);
    request.set_row(row);
    request.set_new_file_name(new_file_name);



    // Container for the data we expect from the server.
    LocalRenameReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->localRenameFifo(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      std::string res = "";
      if(reply.is_successful()){
        res = "true";
      }else{
        res = "false";
      }     
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string localMoveFifo(std::string row,  std::string file_type, std::string path_name, std::string new_path){
    // Data we are sending to the server.
    LocalMoveRequest request;
    request.set_path_name(path_name);
    request.set_file_type(file_type);
    request.set_row(row);
    request.set_new_path(new_path);



    // Container for the data we expect from the server.
    LocalMoveReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->localMoveFifo(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      std::string res = "";
      if(reply.is_successful()){
        res = "true";
      }else{
        res = "false";
      }     
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }



 private:
  std::unique_ptr<Bigtable::Stub> stub_;
};


// Logic and data behind the server's behavior.
class TableServiceImpl final : public Bigtable::Service {
  Status put(ServerContext* context, const PutRequest* request,
                  PutReply* reply) override {

    // primary get mutli req from same user (diff nodes), primary sort them and send the order of req to other nodes
    // 3,2,1 -> every worker node process in the same order ?? when will the worker node will respond to front-end client?
    // primary send out req 3, w1 proc 3, w2 (3) proc 3, send ok back primary -> primary send ok to w2->respond to client
    // forward request to primary and wait for ok and order from primary
    // only primary node gets to generate file_id, then pass it to other worker nodes.
    // std::cout<<"enter put bigtable!"<<" is primary "<<storage->is_primary<<std::endl;
    std::string file_id = "";
    if(!storage->is_primary){
        // forward to primary node, call primary node grpc server_put()
        std::string primary_full_ip = storage->primary_addr->ip + ":" + std::to_string(storage->primary_addr->port);
        // std::cout<<"primary full ip is "<<primary_full_ip<<std::endl;
        TableClient primary_node(grpc::CreateChannel(primary_full_ip, grpc::InsecureChannelCredentials()));
        std::string inner_rpc_reply = primary_node.put(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->data());
        std::cout<<"calling primary!"<<std::endl;       
        while(inner_rpc_reply == "RPC failed"){
          inner_rpc_reply = primary_node.put(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->data());
        }
        file_id = inner_rpc_reply;
    }else{
       //apply row lock
        storage->table.lock_row(request->row()); 
        file_id = storage->localPut(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->data());
        std::cout << "File ID 1 " << file_id << std::endl;
        for(int i = 0; i < storage->all_sub_addr.size(); i++){
          std::string curr_sub_addr = storage->all_sub_addr.at(i).ip + ":" + std::to_string(storage->all_sub_addr.at(i).port);
          TableClient worker_node(grpc::CreateChannel(curr_sub_addr, grpc::InsecureChannelCredentials()));

           std::cout<<"calling other worker from primary! "<<curr_sub_addr<<std::endl;
          std::string inner_rpc_reply = worker_node.localPut_with_fileid(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), file_id, request->data());
          while(inner_rpc_reply == "RPC failed" || inner_rpc_reply != file_id){
            inner_rpc_reply = worker_node.localPut_with_fileid(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), file_id, request->data());
          } 
        }
         // unlock
        storage->table.unlock_row(request->row());
    }
   
    reply->set_file_id(file_id);
    std::cout << "File ID 2 " << reply->file_id() << std::endl;
    return Status::OK;
  }

  Status get(ServerContext* context, const GetRequest* request,
                  GetReply* reply) override {
    //apply row lock
    // storage->table.lock_row(request->row()); 
    std::string res = storage->table.get(request->row(), request->col());
    reply->set_file_content(res);
    // unlock
    // storage->table.unlock_row(request->row());
    return Status::OK;
  }

   Status cput(ServerContext* context, const CPutRequest* request,
                  CPutReply* reply) override {
    bool res;
    if(!storage->is_primary){
        // forward to primary node, call primary node grpc server_put()
        std::string primary_full_ip = storage->primary_addr->ip + ":" + std::to_string(storage->primary_addr->port);
        // std::cout<<"primary full ip is "<<primary_full_ip<<std::endl;
        TableClient primary_node(grpc::CreateChannel(primary_full_ip, grpc::InsecureChannelCredentials()));
        std::string inner_rpc_reply = primary_node.cput(request->new_created_time(), request->new_size(), request->path_name(), request->file_type(), request->row(), request->col(), request->old_data(), request->new_data());
        std::cout<<"calling primary!"<<std::endl;       
        while(inner_rpc_reply == "RPC failed"){
          inner_rpc_reply = primary_node.cput(request->new_created_time(), request->new_size(), request->path_name(), request->file_type(), request->row(), request->col(), request->old_data(), request->new_data());
        }
    }else{
        bool worker_res;
        storage->table.lock_row(request->row());
        // std::cout<<"primary!"<<std::endl;
        res = storage->localCPut(request->new_created_time(), request->new_size(), request->path_name(), request->file_type(), request->row(), request->col(), request->old_data(), request->new_data());
        for(int i = 0; i < storage->all_sub_addr.size(); i++){
          std::string curr_sub_addr = storage->all_sub_addr.at(i).ip + ":" + std::to_string(storage->all_sub_addr.at(i).port);
          TableClient worker_node(grpc::CreateChannel(curr_sub_addr, grpc::InsecureChannelCredentials()));
           // std::cout<<"calling other worker from primary!"<<std::endl;
          std::string inner_rpc_reply = worker_node.localCPut(request->new_created_time(), request->new_size(), request->path_name(), request->file_type(), request->row(), request->col(), request->old_data(), request->new_data());
          if(inner_rpc_reply == "false") worker_res = false;
          else worker_res = true;
          while(inner_rpc_reply == "RPC failed" || worker_res != res){
            inner_rpc_reply = worker_node.localCPut(request->new_created_time(), request->new_size(), request->path_name(), request->file_type(), request->row(), request->col(), request->old_data(), request->new_data());
          }
        }
        storage->table.unlock_row(request->row());
    }
    // std::string prefix("Hello ");
    
    reply->set_is_successful(res);
    return Status::OK;
  }

   Status table_delete(ServerContext* context, const DelRequest* request,
                  DelReply* reply) override {
    // std::string prefix("Hello ");
    bool res;
    if(!storage->is_primary){
        // forward to primary node, call primary node grpc server_put()
        std::string primary_full_ip = storage->primary_addr->ip + ":" + std::to_string(storage->primary_addr->port);
        // std::cout<<"primary full ip is "<<primary_full_ip<<std::endl;
        TableClient primary_node(grpc::CreateChannel(primary_full_ip, grpc::InsecureChannelCredentials()));
        std::string inner_rpc_reply = primary_node.table_delete(request->row(), request->col(), request->file_type(), request->path_name());
        std::cout<<"calling primary!"<<std::endl;       
        while(inner_rpc_reply == "RPC failed"){
          inner_rpc_reply = primary_node.table_delete(request->row(), request->col(), request->file_type(), request->path_name());
        }
    }else{
        bool worker_res;
        storage->table.lock_row(request->row());
        // std::cout<<"primary!"<<std::endl;
        res = storage->localDelete(request->row(), request->col(), request->file_type(), request->path_name());
        for(int i = 0; i < storage->all_sub_addr.size(); i++){
          std::string curr_sub_addr = storage->all_sub_addr.at(i).ip + ":" + std::to_string(storage->all_sub_addr.at(i).port);
          TableClient worker_node(grpc::CreateChannel(curr_sub_addr, grpc::InsecureChannelCredentials()));
           // std::cout<<"calling other worker from primary!"<<std::endl;
          std::string inner_rpc_reply = worker_node.localDelete(request->row(), request->col(), request->file_type(), request->path_name());
          if(inner_rpc_reply == "false") worker_res = false;
          else worker_res = true;
          while(inner_rpc_reply == "RPC failed" || worker_res != res){
            inner_rpc_reply = worker_node.localDelete(request->row(), request->col(), request->file_type(), request->path_name());
          }
        }
        storage->table.unlock_row(request->row());
    }

    reply->set_is_successful(res);
    return Status::OK;
  }


  Status list_all_files(ServerContext* context, const GetFileListRequest* request,
                  GetFileListReply* reply) override {
    // std::string prefix("Hello ");
    vector<FileMetaData> res = storage->table.list_all_files(request->row(), request->path_name());
    // cout<<"request row is "<<request->row()<<" res size is "<<res.size()<<endl;
    if(!res.empty()){
      for(int i = 0; i < res.size(); i++){
        // std::cout<<res.at(i).file_name<<std::endl;
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


     bool res;
    if(!storage->is_primary){
        // forward to primary node, call primary node grpc server_put()
        std::string primary_full_ip = storage->primary_addr->ip + ":" + std::to_string(storage->primary_addr->port);
        // std::cout<<"primary full ip is "<<primary_full_ip<<std::endl;
        TableClient primary_node(grpc::CreateChannel(primary_full_ip, grpc::InsecureChannelCredentials()));
        std::string inner_rpc_reply = primary_node.rename_file_folder(request->row(), request->file_type(), request->path_name(), request->new_file_name());
        std::cout<<"calling primary!"<<std::endl;       
        while(inner_rpc_reply == "RPC failed"){
          inner_rpc_reply = primary_node.rename_file_folder(request->row(), request->file_type(), request->path_name(), request->new_file_name());
        }
    }else{
        bool worker_res;
        storage->table.lock_row(request->row());
        std::cout<<"primary in rename_file_folder "<<std::endl;
        res = storage->localRenameFifo(request->row(), request->file_type(), request->path_name(), request->new_file_name());
        for(int i = 0; i < storage->all_sub_addr.size(); i++){
          std::string curr_sub_addr = storage->all_sub_addr.at(i).ip + ":" + std::to_string(storage->all_sub_addr.at(i).port);
          TableClient worker_node(grpc::CreateChannel(curr_sub_addr, grpc::InsecureChannelCredentials()));
           // std::cout<<"calling other worker from primary!"<<std::endl;
          std::string inner_rpc_reply = worker_node.localRenameFifo(request->row(), request->file_type(), request->path_name(), request->new_file_name());
          if(inner_rpc_reply == "false") worker_res = false;
          else worker_res = true;
          while(inner_rpc_reply == "RPC failed" || worker_res != res){
            inner_rpc_reply = worker_node.localRenameFifo(request->row(), request->file_type(), request->path_name(), request->new_file_name());
          }
      }
      storage->table.unlock_row(request->row());
    }

    reply->set_is_successful(res);
    return Status::OK;
   }

   Status move_file_folder(ServerContext* context, const MoveFifoRequest* request,
                  MoveFifoReply* reply) override {
      

    bool res;
    if(!storage->is_primary){
        // forward to primary node, call primary node grpc server_put()
        std::string primary_full_ip = storage->primary_addr->ip + ":" + std::to_string(storage->primary_addr->port);
        // std::cout<<"primary full ip is "<<primary_full_ip<<std::endl;
        TableClient primary_node(grpc::CreateChannel(primary_full_ip, grpc::InsecureChannelCredentials()));
        std::string inner_rpc_reply = primary_node.move_file_folder(request->row(), request->file_type(), request->path_name(), request->new_path());
        std::cout<<"calling primary!"<<std::endl;       
        while(inner_rpc_reply == "RPC failed"){
          inner_rpc_reply = primary_node.move_file_folder(request->row(), request->file_type(), request->path_name(), request->new_path());
        }
    }else{
        bool worker_res;
        storage->table.lock_row(request->row());
        // std::cout<<"primary!"<<std::endl;
        res = storage->localMoveFifo(request->row(), request->file_type(), request->path_name(), request->new_path());
        for(int i = 0; i < storage->all_sub_addr.size(); i++){
          std::string curr_sub_addr = storage->all_sub_addr.at(i).ip + ":" + std::to_string(storage->all_sub_addr.at(i).port);
          TableClient worker_node(grpc::CreateChannel(curr_sub_addr, grpc::InsecureChannelCredentials()));
           // std::cout<<"calling other worker from primary!"<<std::endl;
          std::string inner_rpc_reply = worker_node.localMoveFifo(request->row(), request->file_type(), request->path_name(), request->new_path());
          if(inner_rpc_reply == "false") worker_res = false;
          else worker_res = true;
          while(inner_rpc_reply == "RPC failed" || worker_res != res){
            inner_rpc_reply = worker_node.localMoveFifo(request->row(), request->file_type(), request->path_name(), request->new_path());
          }
        }
        storage->table.unlock_row(request->row());
    }

    reply->set_is_successful(res);
      return Status::OK;
   }

   Status localPut_with_fileid(ServerContext* context, const LocalPutWithIDRequest* request,
                  LocalPutWithIDReply* reply) override {
    std::string file_id = storage->localPut_with_fileid(request->created_time(), request->size(), request->path_name(), request->file_type(), request->file_from(), request->row(), request->col(), request->data());
    reply->set_file_id(file_id);
    return Status::OK;
  }

  Status localCPut(ServerContext* context, const LocalCPutRequest* request,
                  LocalCPutReply* reply) override {
    bool ret  = storage->localCPut(request->new_created_time(), request->new_size(), request->path_name(), request->file_type(), request->row(), request->col(), request->old_data(), request->new_data());
    reply->set_is_successful(ret);
    return Status::OK;
  }


  Status localDelete(ServerContext* context, const LocalDelRequest* request,
                  LocalDelReply* reply) override {
    bool ret  = storage->localDelete(request->row(), request->col(), request->file_type(), request->path_name());
    reply->set_is_successful(ret);
    return Status::OK;
  }

   Status localRenameFifo(ServerContext* context, const LocalRenameRequest* request,
                  LocalRenameReply* reply) override {
    bool ret  = storage->localRenameFifo(request->row(), request->file_type(), request->path_name(), request->new_file_name());
    reply->set_is_successful(ret);
    return Status::OK;
  }

   Status localMoveFifo(ServerContext* context, const LocalMoveRequest* request,
                  LocalMoveReply* reply) override {
    bool ret  = storage->localMoveFifo(request->row(), request->file_type(), request->path_name(), request->new_path());
    reply->set_is_successful(ret);
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
  storage->readConfigFile(config_file, index); // also check the primary and sublist

  std::string self_full_ip = storage->self_addr.ip + ":" + std::to_string(storage->self_addr.port);
  RunStorageServer(self_full_ip);

  return 0;
}
