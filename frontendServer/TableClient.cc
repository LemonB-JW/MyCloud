#include "TableClient.h"



TableClient::TableClient(std::shared_ptr<Channel> channel)
: stub_(Bigtable::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  // bool put(string created_time, int size, string file_name, string file_type, string file_from, string row, string col, string data) {
std::string TableClient::put(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string user,
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

std::string TableClient::localPut_with_fileid(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string user,
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

std::string TableClient::getEmail(std::string user, std::string fileID) {
  GetRequest req;
  req.set_row(user);
  req.set_col(fileID);

  GetReply reply;

  ClientContext context;

    // The actual RPC.
  Status status = stub_->get(&context, req, &reply);

    // Act upon its status.
  if (status.ok()) {
    return reply.file_content();
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
    << std::endl;
    return "RPC failed";
  }

}

std::vector<FileMetaData> TableClient::listEmails(std::string user){

  GetEmailListRequest req;
  req.set_row(user);

  GetEmailListReply reply;

  ClientContext context;

    // The actual RPC.
  Status status = stub_->list_all_emails(&context, req, &reply);

    // Act upon its status.
  if (status.ok()) {
    return ListEmailsFromReply(reply);
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
    << std::endl;
    std::vector<FileMetaData> v;
    return v;
  }

}
std::vector<FileMetaData> TableClient::list_all_files(std::string row, std::string path_name){
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


std::vector<FileMetaData> TableClient::ListFileFromReply(const bigtable::GetFileListReply& file_list_reply) {
    std::vector<FileMetaData> file_list;

    for (int i = 0; i < file_list_reply.metadata_size(); i++) {
        const bigtable::fileMetaData& mdata = file_list_reply.metadata(i);

        std::cout << "File ID: " << mdata.file_id() << std::endl;
        std::cout << "  Name: " << mdata.file_name() << std::endl;
        FileMetaData file_info(mdata.created_time(), mdata.size(), mdata.file_name(), mdata.file_type(), mdata.file_from(), mdata.file_id());
        file_list.push_back(file_info);

    }

    return file_list;
}



std::vector<FileMetaData> TableClient::ListEmailsFromReply(const bigtable::GetEmailListReply& email_list_reply) {
  
  std::vector<FileMetaData> email_list;

  for (int i = 0; i < email_list_reply.metadata_size(); i++) {
    const bigtable::fileMetaData& mdata = email_list_reply.metadata(i);

    // cout << "File ID: " << mdata.file_id() << endl;
    // cout << "  Name: " << mdata.file_name() << endl;
    FileMetaData file_info(mdata.created_time(), mdata.size(), mdata.file_name(), mdata.file_type(), mdata.file_from(), mdata.file_id());
    email_list.push_back(file_info);
    
  }

  return email_list;
}

std::string TableClient::deleteEmail(std::string row, std::string col, std::string file_type, std::string path_name){
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

std::string TableClient::rename_file_folder(std::string row, std::string file_type, std::string path_name, std::string new_file_name){
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



// int main(int argc, char** argv) {
//   TableClient greeter(grpc::CreateChannel(
//     "localhost:50051", grpc::InsecureChannelCredentials()));


//   bool reply = greeter.put("2019/11/20", 1, "foo.txt", "file", "alice", "janice", "id1", "Welcome");

//   std::cout << "Greeter received: " << reply << std::endl;

//   return 0;
// }
