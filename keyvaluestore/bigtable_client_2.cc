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

  std::string get(std::string row, std::string col){
    // Data we are sending to the server.
    GetRequest request;
    
    request.set_row(row);
    request.set_col(col);

    // Container for the data we expect from the server.
    GetReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->get(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.file_content();
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

  std::vector<FileMetaData> list_all_files(std::string row, std::string path_name){
    // Data we are sending to the server.
    GetFileListRequest request;
    request.set_path_name(path_name);
    request.set_row(row);

    // Container for the data we expect from the server.
    GetFileListReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->list_all_files(&context, request, &reply);
    std::vector<FileMetaData> res;
    // Act upon its status.
    if (status.ok()) {
      res = ListFileFromReply(reply);
      return res;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return res;
    }

  }

 private:
  std::unique_ptr<Bigtable::Stub> stub_;
};

int main(int argc, char** argv) {
  TableClient table(grpc::CreateChannel(
      "localhost:5003", grpc::InsecureChannelCredentials()));

  // string fileID1 = table.put("2019/11/20", 0, "root", "folder", "alice", "janice", "NULL");
  // cout<<"file_id 1"<<endl;
  // string val = table.get("janice", fileID1);
  // cout<<"get val"<<endl;
  string fileID3 = table.put("2019/11/20", 0, "root/doc", "folder", "alice", "janice", "NULL");
  cout<<"file_id 3"<<endl;
  string fileID2 = table.put("2019/11/20", 20, "root/doc/boo.txt", "file", "alice", "janice", "Welcome\n");
  cout<<"file_id 2"<<endl;
  string fileID4 = table.put("2019/11/20", 10, "root/doc/foo.txt", "file", "alice", "janice", "Hellooo\n");
  cout<<"file_id 4"<<endl;

  sleep(2);
  table.rename_file_folder("janice", "folder", "root/doc", "helper");
  cout<<"rename_file_folder"<<endl;
  table.move_file_folder("janice","file", "root/doc/foo.txt", "root/foo.txt");
  cout<<"move_file_folder"<<endl;
  std::vector<FileMetaData> all_files = table.list_all_files("janice","root/helper");
  cout<<"list_all_files"<<endl;
  if(all_files.empty()) cout<<"not exist folder / file.."<<endl;
  else{
    for(int i = 0; i < all_files.size(); i++){
      std::cout<<"file name is "<<all_files.at(i).file_name<<endl;
      std::cout<<"file content is "<<table.get("janice", all_files.at(i).file_id)<<endl;
    }
  }


  return 0;
}
