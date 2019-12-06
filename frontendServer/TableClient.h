
#ifndef TABLECLIENT_H
#define TABLECLIENT_H

#include <iostream>
#include <memory>
#include <string>
#include <stdbool.h>
#include <grpcpp/grpcpp.h>
#include "../lib/FileMetaData.h"

#ifdef BAZEL_BUILD
#include "../keyvaluestore/bigtable.grpc.pb.h"
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
using bigtable::DelRequest;
using bigtable::DelReply;


class TableClient {

public:

    TableClient(std::shared_ptr<Channel> channel);

    std::string put(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string user,
                    std::string file_content);

//    std::string cput(std::string new_created_time, int new_size, std::string path_name, std::string file_type, std::string row, std::string col,
//                     std::string old_data, std::string new_data);

    std::vector<FileMetaData> list_all_files(string row, string path_name);

    std::vector<FileMetaData> ListFileFromReply(const bigtable::GetFileListReply& file_list_reply);

//
//    std::string rename_file_folder(std::string row, std::string file_type, std::string path_name, std::string new_file_name);
//
//    std::string move_file_folder(std::string row, std::string file_type, std::string path_name, std::string new_path);

    std::string localPut_with_fileid(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string user,
                                     std::string file_id, std::string file_content);

    std::string localCPut(std::string new_created_time, int new_size, std::string path_name, std::string file_type, std::string row, std::string col,
                          std::string old_data, std::string new_data);

    std::string localDelete(std::string row, std::string col,
                            std::string file_type, std::string path_name);

    std::string table_delete(std::string row, std::string col, std::string file_type, std::string path_name);

    std::string getEmail(std::string user, std::string fileID);

    std::vector<FileMetaData> listEmails(std::string user);

    std::string deleteEmail(std::string row, std::string col, std::string file_type, std::string path_name);

    std::vector<FileMetaData> ListEmailsFromReply(const bigtable::GetEmailListReply& email_list_reply);


private:
    std::unique_ptr<Bigtable::Stub> stub_;
};

#endif